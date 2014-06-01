#include "MoveSequenceSystem.hh"
#include "MoveSequenceComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveSequenceSystem::MoveSequenceSystem() : ASystem("MoveSequenceSystem")
{}

MoveSequenceSystem::~MoveSequenceSystem()
{}

bool MoveSequenceSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("MoveSequenceComponent") &&
      entity->hasComponent("ActionComponent"))
    return (true);
  return (false);
}

void MoveSequenceSystem::processEntity(Entity *entity, const float delta)
{
  ActionComponent		*actionComponent;
  MoveSequenceComponent		*moveComponent;

  actionComponent = entity->getComponent<ActionComponent>("ActionComponent");
  moveComponent = entity->getComponent<MoveSequenceComponent>("MoveSequenceComponent");

  if (actionComponent && moveComponent)
    {
      actionComponent->setAction(moveComponent->getAction(), true);
      moveComponent->incrementTick(delta);
    }
}
