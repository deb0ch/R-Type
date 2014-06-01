#include <iostream>

#include "EntityDeletedEvent.hh"
#include "AutoDestructComponent.hh"
#include "AutoDestructSystem.hh"

AutoDestructSystem::AutoDestructSystem() : ASystem("AutoDestructSystem") {
}

AutoDestructSystem::~AutoDestructSystem() {
}

bool	AutoDestructSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("AutoDestructComponent"))
    return (true);
  return (false);
}

void	AutoDestructSystem::processEntity(Entity *entity, const float delta)
{
  AutoDestructComponent *autoDestructComponent;
  autoDestructComponent = entity->getComponent<AutoDestructComponent>("AutoDestructComponent");

  autoDestructComponent->setTick(autoDestructComponent->getTick() + delta);
  if (autoDestructComponent->getTick() >= autoDestructComponent->getDelay())
    this->_world->sendEvent(new EntityDeletedEvent(entity));
}
