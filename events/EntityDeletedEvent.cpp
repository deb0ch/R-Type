#include "EntityDeletedEvent.hh"

EntityDeletedEvent::EntityDeletedEvent(Entity *entity) :
  AEvent("EntityDeletedEvent")
{
  this->_entity = entity;
}

EntityDeletedEvent::~EntityDeletedEvent()
{}

Entity *EntityDeletedEvent::getEntity(void) {
  return this->_entity;
}
