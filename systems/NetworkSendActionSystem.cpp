#include "NetworkSendActionSystem.hh"
#include "InputChangedEvent.hh"
#include "Room.hh"
#include "NetworkSendUpdateSystem.hh"
#include "ActionComponent.hh"
#include "NetworkSendActionComponent.hh"
#include "LockGuard.hpp"

NetworkSendActionSystem::NetworkSendActionSystem(const std::vector<std::string> &serializable_action)
  : ASystem("NetworkSendActionSystem"), _serializable_action(serializable_action)
{
  this->_network = NULL;
  this->_room_name = NULL;
}

NetworkSendActionSystem::~NetworkSendActionSystem()
{}

void NetworkSendActionSystem::beforeProcess(const float)
{
  if (!this->_network)
    this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  if (!this->_room_name)
    this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

bool NetworkSendActionSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("ActionComponent") && entity->hasComponent("NetworkSendActionComponent"))
    return (true);
  return (false);
}

void NetworkSendActionSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action_component = entity->getComponent<ActionComponent>("ActionComponent");
  NetworkSendActionComponent	*network_component =
    entity->getComponent<NetworkSendActionComponent>("NetworkSendActionComponent");
  IBuffer			*tmp;
  bool				changed = false;

  if (!this->_network || !this->_room_name)
    return ;
  tmp = this->_network->getUDPBuffer();
  *tmp << static_cast<char>(ACTION_UPDATE);
  *tmp << network_component->getRemoteId();
  *tmp << network_component->getPacketNumber();
  std::for_each(this->_serializable_action.begin(), this->_serializable_action.end(),
		[&tmp, &changed, &action_component] (const std::string &action_name)
		{
		  *tmp << action_name;
		  *tmp << static_cast<char>(action_component->isActive(action_name));
		  action_component->resetChange(action_name);
		});
  Room *room = this->_network->getRoom(*this->_room_name);
  if (room)
    {
      auto guard = create_lock(*room, true);

      room->sendBroadcastUDP(*this->_network, tmp);
    }
  network_component->increasePacketNumber();
}
