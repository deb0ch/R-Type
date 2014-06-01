#include	"ActionFireSystem.hh"
#include	"ActionComponent.hh"
#include	"EntitySpawnerComponent.hh"

ActionFireSystem::ActionFireSystem() : ASystem("ActionFireSystem")
{}

ActionFireSystem::~ActionFireSystem()
{}

bool		ActionFireSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("ActionComponent")
      && entity->hasComponent("EntitySpawnerComponent"))
    return (true);
  return (false);
}

void		ActionFireSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action;
  EntitySpawnerComponent	*spawner;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  spawner = entity->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent");

  spawner->setActive(action->isActive("FIRE"));
}
