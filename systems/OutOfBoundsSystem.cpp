#include <iostream>

#include "Pos2DComponent.hh"
#include "EntityDeletedEvent.hh"
#include "OutOfBoundsSystem.hh"

OutOfBoundsSystem::OutOfBoundsSystem()
  : ASystem("OutOfBoundsSystem")
{}

OutOfBoundsSystem::~OutOfBoundsSystem()
{}

//----- ----- Methods ----- ----- //
bool		OutOfBoundsSystem::canProcess(Entity *e)
{
  if (e->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void		OutOfBoundsSystem::processEntity(Entity *e, const float)
{
  Pos2DComponent	*pos;

  if (!(pos = e->getComponent<Pos2DComponent>("Pos2DComponent")))
    return ;
  if ((pos->getX() >= 800 + 50 || pos->getX() <= 0 - 50) ||
      (pos->getY() >= 600 + 50 || pos->getY() <= 0 - 50)) {
    this->_world->sendEvent(new EntityDeletedEvent(e));
  }
}