#include <iostream>
#include "NetworkSendUpdateSystem.hh"
#include "ISerializableComponent.hh"
#include "INetworkSerializableComponent.hh"
#include "IComponent.hh"
#include "NetworkSendUpdateComponent.hh"
#include "NetworkBuffer.hh"
#include "Hash.hh"

NetworkSendUpdateSystem::NetworkSendUpdateSystem(const std::vector<std::string> &component_to_send)
  : ASystem("NetworkSendUpdateSystem")
{
  this->_component_to_send = component_to_send;
}

NetworkSendUpdateSystem::~NetworkSendUpdateSystem()
{}

bool				NetworkSendUpdateSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("NetworkSendUpdateComponent") &&
      this->_network != NULL && this->_room_name != NULL)
    return (true);
  return (false);
}

void				NetworkSendUpdateSystem::beforeProcess()
{
  this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

void				NetworkSendUpdateSystem::serializeComponents(Entity *entity,
									     IBuffer &buffer)
{
  INetworkSerializableComponent	*serializable_component;
  IComponent			*component;
  Hash				hash;

  for (auto it = this->_component_to_send.begin(); it != this->_component_to_send.end(); ++it)
    {
      if ((serializable_component = entity->getComponent<INetworkSerializableComponent>(*it)) &&
	  (component = dynamic_cast<IComponent *>(serializable_component)))
	{
	  buffer << static_cast<std::size_t>(hash(component->getType()));
	  serializable_component->serialize(buffer);
	}
    }
}

void				NetworkSendUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkSendUpdateComponent	*network_component;
  IBuffer			*buffer;
  Room				*room;

  buffer = this->_network->getUDPBuffer();
  network_component = entity->getComponent<NetworkSendUpdateComponent>("NetworkSendUpdateComponent");
  *buffer << static_cast<char>(ENTITY_UPDATE);
  *buffer << entity->_id;
  *buffer << network_component->getPacketNumber();
  *buffer << static_cast<char>(1);
  this->serializeComponents(entity, *buffer);
  network_component->increasePacketNumber();
  room = this->_network->getRoom(*this->_room_name);
  room->sendBroadcastUDP(*this->_network, buffer);
  room->unlock();
}
