#include	"FireAlwaysSystem.hh"
#include	"ActionComponent.hh"
#include	"FireAlwaysComponent.hh"

FireAlwaysSystem::FireAlwaysSystem() : ASystem("FireAlwaysSystem")
{}

FireAlwaysSystem::~FireAlwaysSystem()
{}

bool		FireAlwaysSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("ActionComponent") &&
      entity->hasComponent("FireAlwaysComponent"))
    return (true);
  return (false);
}

void		FireAlwaysSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  if (!action)
    return ;
  action->setAction("FIRE", true);
}
