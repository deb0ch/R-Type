#include "ResetActionSystem.hh"
#include "ActionComponent.hh"

ResetActionSystem::ResetActionSystem()
: ASystem("ResetActionSystem", 15)
{}

ResetActionSystem::~ResetActionSystem()
{}

bool ResetActionSystem::canProcess(Entity *entity)
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
		action->setAction("UP", false);
		action->setAction("LEFT", false);
		action->setAction("RIGHT", false);
		action->setAction("DOWN", false);
	}
}