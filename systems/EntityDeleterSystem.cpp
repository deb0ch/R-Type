#include <iostream>
#include <map>

#include "EntityDeleterSystem.hh"
#include "EntityDeletedEvent.hh"

EntityDeleterSystem::EntityDeleterSystem()
  : ASystem("EntityDeleterSystem", 0)
{
}

EntityDeleterSystem::~EntityDeleterSystem()
{}

bool		EntityDeleterSystem::canProcess(Entity *) {
  return (false);
}

void	EntityDeleterSystem::processEntity(Entity *, const float){
}

void	EntityDeleterSystem::afterProcess() {
  for_each(this->_toDelete.begin(),
	   this->_toDelete.end(),
	   [this] (Entity *entity) {
	     this->_world->removeEntity(entity);
	   });
  this->_toDelete.clear();
}

void EntityDeleterSystem::addEntityToDelete(IEvent *event) {
  EntityDeletedEvent *entityDeletedEvent = dynamic_cast<EntityDeletedEvent *>(event);

  if (entityDeletedEvent)
    {
      if (Entity *entity = entityDeletedEvent->getEntity())
	{
	  std::vector<Entity *>::iterator it = std::find(this->_toDelete.begin(),
							 this->_toDelete.end(), entity);
	  if (it == this->_toDelete.end())
	    {
	      this->_toDelete.push_back(entity);
	    }
	}
    }
}
