#include "CollisionEvent.hh"

CollisionEvent::CollisionEvent(Entity* entity1, Entity* entity2) : AEvent("CollisionEvent")
{
  this->entity1 = entity1;
  this->entity2 = entity2;
}

CollisionEvent::~CollisionEvent()
{}

const Entity*	CollisionEvent::getEntity1() const
{
  return (this->entity1);
}

const Entity*	CollisionEvent::getEntity2() const
{
  return (this->entity2);
}

Entity*	CollisionEvent::getEntity1()
{
  return (this->entity1);
}

Entity*	CollisionEvent::getEntity2()
{
  return (this->entity2);
}
