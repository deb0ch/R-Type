#include "EntityDeletedEvent.hh"
#include "MoveFollowSystem.hh"
#include "MoveFollowComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveFollowSystem::MoveFollowSystem() : ASystem("MoveFollowSystem") {
  this->_deletedElements = std::vector<Entity *>();
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
  Entity *entity = NULL;

  if (entityDeletedEvent != NULL) {
    if ((entity = entityDeletedEvent->getEntity())) {
      this->_deletedElements.push_back(entity);
    }
  }
}

void MoveFollowSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action;
  MoveFollowComponent		*target;
  Entity			*entityToFollow;
  Pos2DComponent		*posEntity;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  target = entity->getComponent<MoveFollowComponent>("MoveFollowComponent");
  posEntity = entity->getComponent<Pos2DComponent>("Pos2DComponent");

  if ((entityToFollow = this->_world->getEntity(target->getIdToFollow())) != NULL)
    {
      auto posToFollow = entityToFollow->getComponent<Pos2DComponent>("Pos2DComponent");
      if (!posToFollow)
	return;
      if (posEntity->getX() < posToFollow->getX())
	action->setAction("RIGHT", true);
      if (posEntity->getX() > posToFollow->getX())
	action->setAction("LEFT", true);
      if (posEntity->getY() < posToFollow->getY())
	action->setAction("DOWN", true);
      if (posEntity->getY() > posToFollow->getY())
	action->setAction("UP", true);
    }
}

void	MoveFollowSystem::afterProcess()
{
  this->_deletedElements.clear();
}
