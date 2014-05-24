#include "NetworkReceiveUpdateSystem.hh"
#include "NetworkReceiveUpdateComponent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "ASerializableComponent.hh"
#include "NetworkBuffer.hh"
#include "ComponentFactory.hpp"
#include "Hash.hh"

NetworkReceiveUpdateSystem::NetworkReceiveUpdateSystem(const std::vector<std::string> &serializable_component)
  : ASystem("NetworkReceiveUpdateSystem")
{
  std::for_each(serializable_component.begin(), serializable_component.end(),
		[this] (const std::string &name)
		{
		  this->_serializable_component[Hash()(name)] = false;
		});
}

NetworkReceiveUpdateSystem::~NetworkReceiveUpdateSystem()
{}

bool				NetworkReceiveUpdateSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("NetworkReceiveUpdateComponent") &&
      this->_network != NULL && this->_room_name != NULL)
    return (true);
  return (false);
}

void				NetworkReceiveUpdateSystem::beforeProcess()
{
  this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

void				NetworkReceiveUpdateSystem::afterProcess()
{
  Room				*room;

  if (!this->_network || !this->_network)
    return ;
  room = this->_network->getRoom(*this->_room_name);
  if (room)
    {
      std::vector<Remote *> &remotes = room->getRemotes();
      std::for_each(remotes.begin(), remotes.end(),
		    [this] (Remote *remote) -> void
		    {
		      LockVector<IBuffer *> &recv_buffer = remote->getRecvBufferUDP();
		      recv_buffer.lock();
		      LockVector<IBuffer *>::iterator it = recv_buffer.begin();
		      while (it != recv_buffer.end())
			{
			  try
			    {
			      this->parsePacket(recv_buffer, it);
			    }
			  catch (std::exception &e)
			    {
			      std::cerr << e.what() << std::endl;
			      this->_network->disposeUDPBuffer(*it);
			      it = recv_buffer.erase(it);
			    }
			}
		      recv_buffer.unlock();
		    });
      room->unlock();
    }
}

void				NetworkReceiveUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkReceiveUpdateComponent	*receive_component;
  Room				*room;

  receive_component = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
  room = this->_network->getRoom(*this->_room_name);

  std::vector<Remote *> &remotes = room->getRemotes();
  std::for_each(remotes.begin(), remotes.end(),
		[this, &entity, &receive_component] (Remote *remote) -> void
		{
		  LockVector<IBuffer *> &recv_buffer = remote->getRecvBufferUDP();
		  recv_buffer.lock();
		  LockVector<IBuffer *>::iterator it = recv_buffer.begin();
		  while (it != recv_buffer.end())
		    {
		      try
			{
			  this->parsePacketOnEntity(entity, receive_component, recv_buffer, it);
			}
		      catch (std::exception &e)
			{
			  std::cerr << e.what() << std::endl;
			  this->_network->disposeUDPBuffer(*it);
			  it = recv_buffer.erase(it);
			}
		    }
		  recv_buffer.unlock();
		});
  room->unlock();
}

// -------------- Private functions --------------

void		NetworkReceiveUpdateSystem::parsePacketOnEntity(Entity *entity,
								NetworkReceiveUpdateComponent *receive_component,
								LockVector<IBuffer *> &vector,
								LockVector<IBuffer *>::iterator &it)
{
  unsigned int	id_entity;
  unsigned int	num_packet;
  char		packet_type;
  IBuffer	*buffer;

  buffer = *it;
  buffer->rewind();
  *buffer >> packet_type;
  if (packet_type == ENTITY_UPDATE)
    {
      this->getEntityInfos(*buffer, id_entity, num_packet);
      if (id_entity == receive_component->getRemoteID())
	{
	  if (num_packet > receive_component->getPacketNum())
	    {
	      this->updateEntity(entity, *buffer);
	      receive_component->setPacketNum(num_packet);
	    }
	  else
	    std::cout << "Packed dropped: " << num_packet << " " <<
	      receive_component->getPacketNum() << std::endl;
	  this->_network->disposeUDPBuffer(buffer);
	  it = vector.erase(it);
	}
      else
	++it;
    }
  else
    ++it;
}

void		NetworkReceiveUpdateSystem::parsePacket(LockVector<IBuffer *> &vector,
							LockVector<IBuffer *>::iterator &it)
{
  unsigned int	id_entity;
  unsigned int	num_packet;
  char		packet_type;
  Entity	*entity;
  IBuffer	*buffer;

  buffer = *it;
  buffer->rewind();
  *buffer >> packet_type;
  if (packet_type == ENTITY_UPDATE)
    {
      this->getEntityInfos(*buffer, id_entity, num_packet);
      if (!this->remoteEntityExists(id_entity))
	{
	  entity = this->_world->createEntity();
	  entity->addComponent(new NetworkReceiveUpdateComponent(id_entity, num_packet));
	  this->updateEntity(entity, *buffer);
	  this->_world->addEntity(entity);
	  this->_network->disposeUDPBuffer(buffer);
	  it = vector.erase(it);
	}
      else
	++it;
    }
  else
    ++it;
}

void				NetworkReceiveUpdateSystem::unserializeComponent(Entity *entity,
										 IBuffer &buffer)
{
  unsigned long			component_hash;
  ASerializableComponent	*serializable_component;
  bool				update = true;

  buffer >> component_hash;
  if (component_hash == 0)
    {
      buffer >> component_hash;
      update = false;
    }
  auto it = this->_serializable_component.find(component_hash);
  if (it == this->_serializable_component.end())
    {
      throw BufferException(&buffer, std::string("Receive an unserializable component: ") +
			    std::to_string(component_hash));
    }
  it->second = true;
  serializable_component =
    entity->getComponent<ASerializableComponent, unsigned long, Hash>(component_hash, Hash());
  if (!serializable_component || update == false)
    {
      ComponentFactory *fact = this->_world->getSharedObject<ComponentFactory>("componentFactory");

      if (!(serializable_component = fact->create(component_hash)))
	{
	  throw BufferException(&buffer, std::string("Cannot create component: ") +
				std::to_string(component_hash));
	}
    }
  serializable_component->unserialize(buffer);
  if (!entity->hasComponent(serializable_component->getType()))
    entity->addComponent(serializable_component);
  else if (update == false)
    delete serializable_component;
}

void				NetworkReceiveUpdateSystem::updateEntity(Entity *entity,
									 IBuffer &buffer)
{
  resetSerializable();
  while (!buffer.end())
    {
      this->unserializeComponent(entity, buffer);
    }
  auto it = entity->_components.begin();
  while (it != entity->_components.end())
    {
      auto it_serializable = this->_serializable_component.find(Hash()((*it)->getType()));
      if (it_serializable != this->_serializable_component.end() && it_serializable->second == false)
  	{
	  std::cout << "deleting: " << (*it)->getType() << std::endl;
  	  delete *it;
  	  it = entity->_components.erase(it);
  	}
      else
  	++it;
    }
}

void				NetworkReceiveUpdateSystem::getEntityInfos(IBuffer &buffer,
									   unsigned int &id_entity,
									   unsigned int &num_packet)
{
  char				force_byte;

  buffer >> id_entity;
  buffer >> num_packet;
  buffer >> force_byte;
}

bool				NetworkReceiveUpdateSystem::remoteEntityExists(unsigned int id)
{
  std::vector<Entity *> &entities = this->_world->getEntities();

  return (std::find_if(entities.begin(), entities.end(), [id] (Entity *entity) -> bool {
	NetworkReceiveUpdateComponent *network_component;

	network_component = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
	if (network_component && network_component->getRemoteID() == id)
	  return (true);
	return (false);
      }) != entities.end());
}

void		NetworkReceiveUpdateSystem::resetSerializable()
{
  for (auto it = this->_serializable_component.begin(); it != this->_serializable_component.end(); ++it)
    {
      it->second = false;
    }
}
