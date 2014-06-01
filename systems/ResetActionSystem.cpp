#include "ResetActionSystem.hh"
#include "ActionComponent.hh"
#include "NetworkReceiveActionComponent.hh"

ResetActionSystem::ResetActionSystem()
: ASystem("ResetActionSystem", 2)
{}

ResetActionSystem::~ResetActionSystem()
{}

bool ResetActionSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("ActionComponent"))
    return (true);
  return (false);
}

void ResetActionSystem::processEntity(Entity *entity, const float)
{
  ActionComponent *action = entity->getComponent<ActionComponent>("ActionComponent");

  if (action != NULL)
    {
      if (entity->hasComponent("NetworkReceiveActionComponent"))
	return ;
      action->setAction("UP", false);
      action->setAction("LEFT", false);
      action->setAction("RIGHT", false);
      action->setAction("DOWN", false);
      action->setAction("FIRE", false);
    }
}
