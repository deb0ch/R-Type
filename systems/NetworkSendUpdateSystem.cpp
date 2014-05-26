#include <iostream>
#include "NetworkSendUpdateSystem.hh"
#include "ASerializableComponent.hh"
#include "IComponent.hh"
#include "NetworkSendUpdateComponent.hh"
#include "NetworkBuffer.hh"
#include "Hash.hh"
#include "LockGuard.hpp"

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
									     Remote *remote,
									     IBuffer &buffer)
{
  ASerializableComponent	*serializable_component;
  Hash				hash;

  for (auto it = this->_component_to_send.begin(); it != this->_component_to_send.end(); ++it)
    {
      if ((serializable_component = entity->getComponent<ASerializableComponent>(*it)))
	{
	  serializable_component->networkSerialize(remote, buffer);
	}
    }
}

void				NetworkSendUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkSendUpdateComponent	*network_component;
  Room				*room;

  room = this->_network->getRoom(*this->_room_name);
  if (room)
    {
      auto guard = create_lock(*room);

      std::vector<Remote *> &remotes = room->getRemotes();
      network_component = entity->getComponent<NetworkSendUpdateComponent>("NetworkSendUpdateComponent");
      std::for_each(remotes.begin(), remotes.end(),
		    [this, &entity, &network_component] (Remote *remote)
		    {
		      IBuffer *buffer = this->_network->getUDPBuffer();
		      *buffer << static_cast<char>(ENTITY_UPDATE);
		      *buffer << entity->_id;
		      *buffer << network_component->getPacketNumber();
		      *buffer << static_cast<char>(1);
		      this->serializeComponents(entity, remote, *buffer);
		      remote->sendUDP(buffer);
		    });
      network_component->increasePacketNumber();
    }
}
