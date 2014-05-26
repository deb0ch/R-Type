#include <iostream>
#include <map>

#include "EntityDeletedEvent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "NetworkSendDieEntitySystem.hh"
#include "LockGuard.hpp"

NetworkSendDieEntitySystem::NetworkSendDieEntitySystem() : ASystem("NetworkSendDieEntitySystem", 0) {
  this->_network = NULL;
  this->_room_name = NULL;
}

NetworkSendDieEntitySystem::~NetworkSendDieEntitySystem() {

}

void NetworkSendDieEntitySystem::beforeProcess(const float)
{
  if (!this->_network)
    this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  if (!this->_room_name)
    this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

bool		NetworkSendDieEntitySystem::canProcess(Entity *)
{
  return (false);
}

void	NetworkSendDieEntitySystem::processEntity(Entity *, const float)
{}

void	NetworkSendDieEntitySystem::afterProcess(const float)
{
  Room *room = NULL;
  auto itEnd = this->_toDelete.end();
  auto it = this->_toDelete.begin();

  if (_network && _room_name && (room = this->_network->getRoom(*this->_room_name)))
    {
      auto guard = create_lock(*room);

      std::vector<Remote *> &remotes = room->getRemotes();
      std::for_each(remotes.begin(), remotes.end(),
		    [this, &it, &itEnd] (Remote *remote)
		    {
		      for (it = this->_toDelete.begin(); it != itEnd; ++it)
			{
			  for (int i = 0; i < 5; ++i)
			    {
			      IBuffer *buffer = this->_network->getUDPBuffer();
			      *buffer << static_cast<char>(KILL_ENTITY);
			      *buffer << (*it)->_id;
			      remote->sendUDP(buffer);
			    }
			}
		    });
    }
  this->_toDelete.clear();
}

void NetworkSendDieEntitySystem::addEntityToDelete(IEvent *event)
{
  EntityDeletedEvent *entityDeletedEvent = dynamic_cast<EntityDeletedEvent *>(event);
  Entity *entity = NULL;

  if (_network && _room_name && entityDeletedEvent &&
      (entity = entityDeletedEvent->getEntity()) &&
      entity->hasComponent("NetworkSendUpdateComponent"))
    {
      std::vector<Entity *>::iterator it = std::find(this->_toDelete.begin(),
						     this->_toDelete.end(), entity);
      if (it == this->_toDelete.end())
	{
	  this->_toDelete.push_back(entity);
	}
    }
}
