#include	"ActionFireSystem.hh"
#include	"ActionComponent.hh"
#include	"EntitySpawnerComponent.hh"

ActionFireSystem::ActionFireSystem() : ASystem("ActionFireSystem")
{}

ActionFireSystem::~ActionFireSystem()
{}

bool		ActionFireSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("ActionComponent") && entity->hasComponent("EntitySpawnerComponent"))
    return (true);
  return (false);
}
#include	<iostream>
void		ActionFireSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action;
  EntitySpawnerComponent	*spawner;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  spawner = entity->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent");

  if (action->isActive("FIRE"))
    spawner->setActive(true);
}
