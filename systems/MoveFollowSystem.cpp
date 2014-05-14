#include "EntityDeletedEvent.hh"
#include "MoveFollowSystem.hh"
#include "MoveFollowComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveFollowSystem::MoveFollowSystem() : ASystem("MoveFollowSystem") {
}

MoveFollowSystem::~MoveFollowSystem()
{}

void MoveFollowSystem::init() {
  this->_world->addEventHandler("EntityDeletedEvent", this,
				&MoveFollowSystem::removeMoveFollowSystem);
}

bool MoveFollowSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("MoveFollowComponent") &&
      entity->hasComponent("ActionComponent") &&
      entity->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void MoveFollowSystem::removeMoveFollowSystem(IEvent *event) {
  EntityDeletedEvent *entityDeletedEvent = dynamic_cast<EntityDeletedEvent *>(event);

  if (entityDeletedEvent) {
    if (Entity *entity = entityDeletedEvent->getEntity()) {
      entity->removeComponent(entity->getComponent<MoveFollowComponent>("MoveFollowComponent"));
    }
  }
}

void MoveFollowSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action = NULL;
  MoveFollowComponent		*target = NULL;
  Pos2DComponent		*posEntity = NULL;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  target = entity->getComponent<MoveFollowComponent>("MoveFollowComponent");
  posEntity = entity->getComponent<Pos2DComponent>("Pos2DComponent");

  action->setAction("UP", false);
  action->setAction("LEFT", false);
  action->setAction("DOWN", false);
  action->setAction("RIGHT", false);

  if (posEntity->getX() < target->getX())
    action->setAction("RIGHT", true);
  /*
  if (posEntity->getX() > target->getX())
    action->setAction("LEFT", true);
  if (posEntity->getY() < target->getY())
    action->setAction("DOWN", true);
  if (posEntity->getY() > target->getY())
    action->setAction("UP", true);
  */
}
