#include "EntityDeletedEvent.hh"

EntityDeletedEvent::EntityDeletedEvent(Entity *entity, bool forced) :
  AEvent("EntityDeletedEvent")
{
  this->_entity = entity;
  this->_forced = forced;
}

EntityDeletedEvent::~EntityDeletedEvent()
{}

Entity *EntityDeletedEvent::getEntity(void) {
  return this->_entity;
}

const Entity *EntityDeletedEvent::getEntity(void) const {
  return this->_entity;
}

bool	EntityDeletedEvent::isForced() const
{
  return (this->_forced);
}
