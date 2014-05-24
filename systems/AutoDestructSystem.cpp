#include <iostream>

#include "EntityDeletedEvent.hh"
#include "AutoDestructComponent.hh"
#include "AutoDestructSystem.hh"

AutoDestructSystem::AutoDestructSystem() : ASystem("AutoDestructSystem") {
}

AutoDestructSystem::~AutoDestructSystem() {
}

bool	AutoDestructSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("AutoDestructComponent"))
    return (true);
  return (false);
}

void	AutoDestructSystem::processEntity(Entity *entity, const float)
{
  AutoDestructComponent *autoDestructComponent;
  autoDestructComponent = entity->getComponent<AutoDestructComponent>("AutoDestructComponent");

  autoDestructComponent->setTick(autoDestructComponent->getTick() + 1);
  if (autoDestructComponent->getTick() >= autoDestructComponent->getDelay())
    this->_world->sendEvent(new EntityDeletedEvent(entity));
}
