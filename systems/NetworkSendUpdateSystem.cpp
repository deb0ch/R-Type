#include <iostream>
#include "NetworkSendUpdateSystem.hh"
#include "ASerializableComponent.hh"
#include "IComponent.hh"
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

bool				NetworkSendUpdateSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("NetworkSendUpdateComponent") &&
      this->_network != NULL && this->_room_name != NULL)
    return (true);
  return (false);
}

void				NetworkSendUpdateSystem::beforeProcess(const float)
{
  this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

void				NetworkSendUpdateSystem::serializeComponents(const Entity *entity,
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

void	NetworkSendUpdateSystem::updateEntityToRemote(Remote *remote, const Entity *entity,
						      NetworkSendUpdateComponent *network_component)
{
  if (!network_component || !entity || !remote)
    return ;
  IBuffer *buffer = this->_network->getUDPBuffer();

  *buffer << static_cast<char>(ENTITY_UPDATE);
  *buffer << entity->_id;
  *buffer << network_component->getPacketNumber();
  *buffer << network_component->getUpdateRate();
  this->serializeComponents(entity, remote, *buffer);
  remote->sendUDP(buffer);
}

void				NetworkSendUpdateSystem::processEntity(Entity *entity, const float delta)
{
  NetworkSendUpdateComponent	*network_component;
  Room				*room;

  room = this->_network->getRoom(*this->_room_name);
  if (room)
    {
      auto guard = create_lock(*room);

      std::vector<Remote *> &remotes = room->getRemotes();
      network_component = entity->getComponent<NetworkSendUpdateComponent>("NetworkSendUpdateComponent");
      network_component->addLastUpdateDelay(delta);
      if (network_component->canSend())
	{
	  network_component->resetLastUpdateDelay();
	  std::for_each(remotes.begin(), remotes.end(),
			[this, &entity, &network_component] (Remote *remote)
			{
			  this->updateEntityToRemote(remote, entity, network_component);
			});
	  network_component->increasePacketNumber();
	}
    }
}
