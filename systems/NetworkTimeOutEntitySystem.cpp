#include "EntityDeletedEvent.hh"
#include "NetworkReceiveUpdateComponent.hh"
#include "NetworkTimeOutEntitySystem.hh"

NetworkTimeOutEntitySystem::NetworkTimeOutEntitySystem() : ASystem("NetworkTimeOutEntitySystem")
{}

NetworkTimeOutEntitySystem::~NetworkTimeOutEntitySystem()
{}

bool		NetworkTimeOutEntitySystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("NetworkReceiveUpdateComponent"))
    return true;
  return false;
}

void		NetworkTimeOutEntitySystem::processEntity(Entity *entity, const float) {
  NetworkReceiveUpdateComponent *tmp;
  tmp = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");

  if (tmp && tmp->getLastUpdate() >= 50)
    this->_world->sendEvent(new EntityDeletedEvent(entity));
}
