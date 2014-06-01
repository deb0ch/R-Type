#include "NetworkReceiveUpdateSystem.hh"
#include "NetworkReceiveUpdateComponent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "ASerializableComponent.hh"
#include "NetworkBuffer.hh"
#include "ComponentFactory.hpp"
#include "Hash.hh"
#include "LockGuard.hpp"

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

bool				NetworkReceiveUpdateSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("NetworkReceiveUpdateComponent") &&
      this->_network != NULL && this->_room_name != NULL)
    return (true);
  return (false);
}

void				NetworkReceiveUpdateSystem::beforeProcess(const float)
{
  this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

void				NetworkReceiveUpdateSystem::afterProcess(const float)
{
  Room				*room;

  if (!this->_network || !this->_network)
    return ;
  room = this->_network->getRoom(*this->_room_name);
  if (room)
    {
      auto guard = create_lock(*room);

      std::vector<Remote *> &remotes = room->getRemotes();
      std::for_each(remotes.begin(), remotes.end(),
		    [this] (Remote *remote) -> void
		    {
		      LockVector<IBuffer *> &recv_buffer = remote->getRecvBufferUDP();
		      auto guard = create_lock(recv_buffer);

		      LockVector<IBuffer *>::iterator it = recv_buffer.begin();
		      while (it != recv_buffer.end())
			{
			  try
			    {
			      this->parsePacket(recv_buffer, it);
			    }
			  catch (const std::exception &e)
			    {
			      std::cerr << "Error while parsing for new entity packet: " << std::endl
					<< e.what() << std::endl;
			      this->_network->disposeUDPBuffer(*it);
			      it = recv_buffer.erase(it);
			    }
			}
		    });
    }
}

void				NetworkReceiveUpdateSystem::processEntity(Entity *entity, const float delta)
{
  NetworkReceiveUpdateComponent	*receive_component;
  Room				*room;

  receive_component = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
  receive_component->addLastUpdate(delta);
  room = this->_network->getRoom(*this->_room_name);

  if (room)
    {
      auto guard = create_lock(*room);

      std::vector<Remote *> &remotes = room->getRemotes();
      std::for_each(remotes.begin(), remotes.end(),
		    [this, &entity, &receive_component] (Remote *remote) -> void
		    {
		      LockVector<IBuffer *> &recv_buffer = remote->getRecvBufferUDP();
		      auto guard = create_lock(recv_buffer);

		      LockVector<IBuffer *>::iterator it = recv_buffer.begin();
		      while (it != recv_buffer.end())
			{
			  try
			    {
			      this->parsePacketOnEntity(entity, receive_component, recv_buffer, it);
			    }
			  catch (const std::exception &e)
			    {
			      std::cerr << "Error while parsing entity packet: " << std::endl
					<< e.what() << std::endl;
			      this->_network->disposeUDPBuffer(*it);
			      it = recv_buffer.erase(it);
			    }
			}
		    });
    }
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
  float		update_rate;

  buffer = *it;
  buffer->rewind();
  *buffer >> packet_type;
  if (packet_type == ENTITY_UPDATE)
    {
      this->getEntityInfos(*buffer, id_entity, num_packet, update_rate);
      if (id_entity == receive_component->getRemoteID())
	{
	  if (num_packet > receive_component->getPacketNum())
	    {
	      receive_component->setUpdateRate(update_rate);
	      this->updateEntity(entity, receive_component, *buffer);
	      receive_component->setPacketNum(num_packet);
	    }
	  else
	    std::cerr << "Packed dropped: " << num_packet << " " <<
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
  float		update_rate;

  buffer = *it;
  buffer->rewind();
  *buffer >> packet_type;
  if (packet_type == ENTITY_UPDATE)
    {
      this->getEntityInfos(*buffer, id_entity, num_packet, update_rate);
      if (!this->remoteEntityExists(id_entity))
	{
	  entity = this->_world->createEntity();
	  NetworkReceiveUpdateComponent *tmp = new NetworkReceiveUpdateComponent(id_entity,
										 num_packet,
										 update_rate);
	  entity->addComponent(tmp);
	  this->updateEntity(entity, tmp, *buffer);
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
  hash_t			component_hash;
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
    entity->getComponent<ASerializableComponent, hash_t, Hash>(component_hash, Hash());
  if (!serializable_component || update == false)
    {
      ComponentFactory *fact = this->_world->getSharedObject<ComponentFactory>("componentFactory");

      if (!(serializable_component = fact->create(component_hash)))
	{
	  throw BufferException(&buffer, std::string("Cannot create component: ") +
				std::to_string(component_hash));
	}
    }
  serializable_component->networkUnSerialize(buffer, this->_world, entity);
  if (!entity->hasComponent(serializable_component->getType()))
    entity->addComponent(serializable_component);
  else if (update == false)
    delete serializable_component;
}

void				NetworkReceiveUpdateSystem::updateEntity(Entity *entity,
									 NetworkReceiveUpdateComponent *receive_comp,
									 IBuffer &buffer)
{
  receive_comp->resetLastUpdate();
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
  	  delete *it;
  	  it = entity->_components.erase(it);
  	}
      else
  	++it;
    }
}

void				NetworkReceiveUpdateSystem::getEntityInfos(IBuffer &buffer,
									   unsigned int &id_entity,
									   unsigned int &num_packet,
									   float &update_rate)
{
  buffer >> id_entity;
  buffer >> num_packet;
  buffer >> update_rate;
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
