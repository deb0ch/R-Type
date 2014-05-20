#include "NetworkReceiveUpdateSystem.hh"
#include "NetworkReceiveUpdateComponent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "ISerializableComponent.hh"
#include "INetworkSerializableComponent.hh"
#include "NetworkBuffer.hh"
#include "ComponentFactory.hpp"

NetworkReceiveUpdateSystem::NetworkReceiveUpdateSystem() : ASystem("NetworkReceiveUpdateSystem")
{}

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
			  this->parsePacket(recv_buffer, it);
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
		      this->parsePacketOnEntity(entity, receive_component, recv_buffer, it);
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
	  delete buffer;
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
  std::cout << "Hereu: " << (int)packet_type << std::endl;
  if (packet_type == ENTITY_UPDATE)
    {
      std::cout << "Here" << std::endl;
      this->getEntityInfos(*buffer, id_entity, num_packet);
      if (!this->remoteEntityExists(id_entity))
	{
	  entity = this->_world->createEntity();
	  entity->addComponent(new NetworkReceiveUpdateComponent(id_entity, num_packet));
	  this->updateEntity(entity, *buffer);
	  this->_world->addEntity(entity);
	  delete buffer;
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
  IComponent			*new_component;
  INetworkSerializableComponent	*serializable_component;

  buffer >> component_hash;
  std::cout << component_hash << std::endl;
  ComponentFactory *test = this->_world->getSharedObject<ComponentFactory>("componentFactory");
  new_component = test->create(component_hash);
  std::cout << new_component << std::endl;
  if (!(serializable_component = dynamic_cast<INetworkSerializableComponent *>(new_component)))
    {
      std::cerr << "Received a no serializable component" << std::endl;
      throw 1;
    }
  serializable_component->unserialize(buffer);
  entity->addComponent(new_component);
}

void				NetworkReceiveUpdateSystem::updateEntity(Entity *entity,
									 IBuffer &buffer)
{
  auto it = entity->_components.begin();
  while (it != entity->_components.end())
    {
      if (dynamic_cast<INetworkSerializableComponent *>(*it) != NULL) // We delete all serializable component
	{
	  delete *it;
	  it = entity->_components.erase(it);
	}
      else
	++it;
    }
  while (!buffer.end())
    {
      this->unserializeComponent(entity, buffer);
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
