#include "MoveFollowSystem.hh"
#include "MoveFollowComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveFollowSystem::MoveFollowSystem() : ASystem("MoveFollowSystem")
{}

MoveFollowSystem::~MoveFollowSystem()
{}

bool MoveFollowSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("MoveFollowComponent") &&
      entity->hasComponent("ActionComponent") &&
      entity->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}
#include	<iostream>
void MoveFollowSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action;
  MoveFollowComponent		*target;
  Pos2DComponent		*pos;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  target = entity->getComponent<MoveFollowComponent>("MoveFollowComponent");
  pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");

  action->setAction("UP", false);
  action->setAction("LEFT", false);
  action->setAction("DOWN", false);
  action->setAction("RIGHT", false);

  std::cout << "EYADHAI9UDHIUEFH" << std::endl;
  if (pos->getX() < target->getX())
    action->setAction("RIGHT", true);
  if (pos->getX() > target->getX())
    action->setAction("LEFT", true);
  if (pos->getY() < target->getY())
    action->setAction("DOWN", true);
  if (pos->getY() > target->getY())
    action->setAction("UP", true);
}
