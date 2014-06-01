#include <iostream>

#include "Pos2DComponent.hh"
#include "EntityDeletedEvent.hh"
#include "TagComponent.hh"
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
  if ((pos->getX() >= WINDOW_WIDTH + 50 || pos->getX() <= 0 - 50) ||
      (pos->getY() >= WINDOW_HEIGHT + 50 || pos->getY() <= 0 - 50)) {

    TagComponent *tmp = e->getComponent<TagComponent>("TagComponent");

    if (tmp && tmp->hasTag("do_not_delete"))
      return;
    this->_world->sendEvent(new EntityDeletedEvent(e, true));
  }
}
