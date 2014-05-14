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

void MoveFollowSystem::processEntity(Entity *entity, const float) {
  ActionComponent *action = entity->getComponent<ActionComponent>("ActionComponent");
  Pos2DComponent *posEntity = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  MoveFollowComponent *target = entity->getComponent<MoveFollowComponent>("MoveFollowComponent");
  Entity *entityToFollow = this->_world->getEntity(target->getIdToFollow());

  action->setAction("UP", false);
  action->setAction("LEFT", false);
  action->setAction("DOWN", false);
  action->setAction("RIGHT", false);
  if (entityToFollow != NULL) {
    auto it = std::find(this->_deletedElements.begin(), this->_deletedElements.end(), entityToFollow);
    if (it != this->_deletedElements.end()) {
      entity->removeComponent(target);
      return ;
    }
    auto posToFollow = entityToFollow->getComponent<Pos2DComponent>("Pos2DComponent");
    if (!posToFollow)
      return ;
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

void	MoveFollowSystem::afterProcess() {
  this->_deletedElements.clear();
}
