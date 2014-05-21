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
  if (entity->hasComponent("NetworkReceiveUpdateComponent") && this->_packets_to_apply != NULL)
    return (true);
  return (false);
}

void				NetworkReceiveUpdateSystem::beforeProcess()
{
  auto				tmp =
    this->_world->getSharedObject< std::vector<NetworkBuffer *> >("LeChevalCestTropGenial");

  if (tmp)
    this->_packets_to_apply = tmp;
}

void				NetworkReceiveUpdateSystem::afterProcess()
{
  unsigned int			id_entity;
  unsigned int			num_packet;
  Entity			*entity;
  NetworkBuffer			*buffer;
  char				packet_type;

  auto it = this->_packets_to_apply->begin();
  while (it != this->_packets_to_apply->end()) // setup a try{}catch here for unserialize
    {
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
	      delete buffer;
	      it = this->_packets_to_apply->erase(it);
	    }
	  else
	    ++it;
	}
      else
	++it;
    }
}

void				NetworkReceiveUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkReceiveUpdateComponent	*receive_component;
  unsigned int			id_entity;
  unsigned int			num_packet;
  char				packet_type;
  NetworkBuffer			*buffer;

  receive_component = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
  auto it = this->_packets_to_apply->begin();
  while (it != this->_packets_to_apply->end()) // setup a try{}catch here for unserialize
    {
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
	      it = this->_packets_to_apply->erase(it);
	    }
	  else
	    ++it;
	}
      else
	++it;
    }
}


// -------------- Private functions --------------

void				NetworkReceiveUpdateSystem::unserializeComponent(Entity *entity,
										 NetworkBuffer &buffer)
{
  std::size_t			component_hash;
  IComponent			*new_component;
  INetworkSerializableComponent	*serializable_component;

  return;
  buffer >> component_hash;
  /*
  VOIR AVEC ROMAIN ICI FACTORY
  */
  std::cout << component_hash << std::endl;
  ComponentFactory *test = this->_world->getSharedObject<ComponentFactory>("componentFactory");
  new_component = test->create(component_hash);
  if (!(serializable_component = dynamic_cast<INetworkSerializableComponent *>(new_component)))
    {
      std::cerr << "Received a no serializable component" << std::endl;
      throw 1;
    }
  serializable_component->unserialize(buffer);
  entity->addComponent(new_component);
}

void				NetworkReceiveUpdateSystem::updateEntity(Entity *entity,
									 NetworkBuffer &buffer)
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

void				NetworkReceiveUpdateSystem::getEntityInfos(NetworkBuffer &buffer,
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
