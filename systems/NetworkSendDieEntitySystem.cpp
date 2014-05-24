#include <iostream>
#include <map>

#include "EntityDeletedEvent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "NetworkSendDieEntitySystem.hh"

NetworkSendDieEntitySystem::NetworkSendDieEntitySystem() : ASystem("NetworkSendDieEntitySystem", 0) {
  this->_network = NULL;
  this->_room_name = NULL;
}

NetworkSendDieEntitySystem::~NetworkSendDieEntitySystem() {

}

void NetworkSendDieEntitySystem::beforeProcess() {
  if (!this->_network)
    this->_network = this->_world->getSharedObject<INetworkRelay>("NetworkRelay");
  if (!this->_room_name)
    this->_room_name = this->_world->getSharedObject<std::string>("RoomName");
}

bool		NetworkSendDieEntitySystem::canProcess(Entity *) {
  return (false);
}

void	NetworkSendDieEntitySystem::processEntity(Entity *, const float){
}

void	NetworkSendDieEntitySystem::afterProcess() {
  Room *room = NULL;
  auto itEnd = this->_toDelete.end();
  auto it = this->_toDelete.begin();

  if (_network && _room_name && (room = this->_network->getRoom(*this->_room_name))) {
    std::vector<Remote *> &remotes = room->getRemotes();
    std::for_each(remotes.begin(), remotes.end(),
		  [this, &it, &itEnd] (Remote *remote) {
		    for (it = this->_toDelete.begin(); it != itEnd; ++it) {
		      IBuffer *buffer = this->_network->getUDPBuffer();
		      *buffer << static_cast<char>(KILL_ENTITY);
		      *buffer << (*it)->_id;
		      for (int i = 0; i < 50; ++i) {
			remote->sendUDP(buffer);
		      }
		    }
		  });
    room->unlock();
  }
  this->_toDelete.clear();
}

void NetworkSendDieEntitySystem::addEntityToDelete(IEvent *event) {
  EntityDeletedEvent *entityDeletedEvent = dynamic_cast<EntityDeletedEvent *>(event);
  Entity *entity = NULL;

  if (_network && _room_name && entityDeletedEvent &&
      (entity = entityDeletedEvent->getEntity()) &&
      entity->hasComponent("NetworkSendUpdateComponent"))
    {
      std::vector<Entity *>::iterator it = std::find(this->_toDelete.begin(),
						     this->_toDelete.end(), entity);
      if (it == this->_toDelete.end()) {
	this->_toDelete.push_back(entity);
      }
    }
}
