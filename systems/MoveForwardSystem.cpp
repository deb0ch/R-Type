#include "MoveForwardSystem.hh"
#include "MoveForwardComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveForwardSystem::MoveForwardSystem() : ASystem("MoveForwardSystem")
{}

MoveForwardSystem::~MoveForwardSystem()
{}

bool MoveForwardSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("MoveForwardComponent") &&
      entity->hasComponent("ActionComponent"))
    return (true);
  return (false);
}

void MoveForwardSystem::processEntity(Entity *entity, const float)
{
  ActionComponent	*action;
  MoveForwardComponent	*moveEntity;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  moveEntity = entity->getComponent<MoveForwardComponent>("MoveForwardComponent");

  action->setAction(moveEntity->getDirection().first, true);
  action->setAction(moveEntity->getDirection().second, true);
}
