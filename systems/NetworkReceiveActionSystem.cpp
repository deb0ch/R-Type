#include "NetworkReceiveActionSystem.hh"
#include "Room.hh"
#include "NetworkSendUpdateSystem.hh"
#include "LockGuard.hpp"

NetworkReceiveActionSystem::NetworkReceiveActionSystem(const std::vector<std::string> &serializable_action)
  : ASystem("NetworkReceiveActionSystem"), _serializable_action(serializable_action)
{
  this->_room_name = NULL;
  this->_network = NULL;
}

NetworkReceiveActionSystem::~NetworkReceiveActionSystem()
{}

void NetworkReceiveActionSystem::beforeProcess(const float)
{
  if (!this->_network)
    this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  if (!this->_room_name)
    this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

bool NetworkReceiveActionSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("ActionComponent") && entity->hasComponent("NetworkReceiveActionComponent"))
    return true;
  return false;
}

void NetworkReceiveActionSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action_component =
    entity->getComponent<ActionComponent>("ActionComponent");
  NetworkReceiveActionComponent	*network_component =
    entity->getComponent<NetworkReceiveActionComponent>("NetworkReceiveActionComponent");
  Room				*room;

  if (!this->_network || !this->_room_name)
    return ;
  room = this->_network->getRoom(*this->_room_name);
  action_component->resetActions();
  if (room)
    {
      auto guard = create_lock(*room);

      std::vector<Remote *> &remotes = room->getRemotes();
      std::for_each(remotes.begin(), remotes.end(),
		    [this, &entity, &action_component, &network_component] (Remote *remote) -> void
		    {
		      LockVector<IBuffer *> &recv_buffer = remote->getRecvBufferUDP();
		      auto guard = create_lock(recv_buffer);

		      LockVector<IBuffer *>::iterator it = recv_buffer.begin();
		      while (it != recv_buffer.end())
			{
			  this->parsePacket(entity, action_component, network_component,
					    recv_buffer, it);
			}
		    });
    }
}

void NetworkReceiveActionSystem::parsePacket(Entity *entity,
					     ActionComponent *action,
					     NetworkReceiveActionComponent *network,
					     LockVector<IBuffer *> &buffers,
					     LockVector<IBuffer *>::iterator &it)
{
  IBuffer	*buffer;
  char		id;
  unsigned int	entity_id;
  unsigned int	packet_number;

  buffer = *it;
  buffer->rewind();
  *buffer >> id;
  if (id == ACTION_UPDATE)
    {
      *buffer >> entity_id;
      if (entity_id == entity->_id)
	{
	  *buffer >> packet_number;
	  if (packet_number > network->getPacketNum())
	    {
	      network->setPacketNum(packet_number);
	      this->parseActions(*buffer, action);
	    }
	  this->_network->disposeUDPBuffer(buffer);
	  it = buffers.erase(it);
	}
      else
	++it;
    }
  else
    ++it;
}

void		NetworkReceiveActionSystem::parseActions(IBuffer &buffer, ActionComponent *action)
{
  std::string	action_name;
  char		active;

  while (!buffer.end())
    {
      buffer >> action_name;
      buffer >> active;
      action->setAction(action_name, active != 0);
    }
}
