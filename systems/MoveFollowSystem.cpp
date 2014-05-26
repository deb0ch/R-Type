
#include "EntityDeletedEvent.hh"
#include "MoveFollowSystem.hh"
#include "MoveFollowComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveFollowSystem::MoveFollowSystem()
  : ASystem("MoveFollowSystem")
{}

MoveFollowSystem::~MoveFollowSystem()
{}

bool MoveFollowSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("MoveFollowComponent") &&
      entity->hasComponent("ActionComponent") &&
      entity->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

inline float	MoveFollowSystem::getDistance(Pos2DComponent* a, Pos2DComponent* b) const
{
  return (sqrt(powf(a->getX() - b->getX(), 2) + powf(a->getY() - b->getY(), 2)));
}

inline bool	MoveFollowSystem::isCloser(Pos2DComponent* follower,
					   Pos2DComponent* prevTarget,
					   Pos2DComponent* newTarget) const
{
  return (getDistance(follower, prevTarget) > getDistance(follower, newTarget));
}

Entity*		MoveFollowSystem::searchClosestTarget(Entity* entity,
						      const std::string & tagToFollow) const
{
  Entity*	target = NULL;

  for (auto it = _world->getEntities().begin() ; it != _world->getEntities().end() ; ++it)
    {
      if ((*it)
	  && (*it)->hasComponent("TagComponent")
	  && (*it)->getComponent<TagComponent>("TagComponent")->hasTag(tagToFollow))
	{
	  if (target == NULL
	      || isCloser(entity->getComponent<Pos2DComponent>("Pos2DComponent"),
			  target->getComponent<Pos2DComponent>("Pos2DComponent"),
			  (*it)->getComponent<Pos2DComponent>("Pos2DComponent")))
	    target = (*it);
	}
    }
  return (target);
}

void MoveFollowSystem::processEntity(Entity *entity, const float)
{
  ActionComponent*		action;
  MoveFollowComponent*		moveFollowComponent;
  Pos2DComponent*		posEntity;
  Entity*			entityToFollow = NULL;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  moveFollowComponent = entity->getComponent<MoveFollowComponent>("MoveFollowComponent");
  posEntity = entity->getComponent<Pos2DComponent>("Pos2DComponent");

  if ((entityToFollow = this->_world->getEntity(moveFollowComponent->getIdToFollow())) == NULL)
    {
      const std::string &	tagToFollow = moveFollowComponent->getTagToFollow();

      entityToFollow = searchClosestTarget(entity, tagToFollow);
    }

  if (entityToFollow != NULL)
    {
      Pos2DComponent*	posToFollow = entityToFollow->getComponent<Pos2DComponent>("Pos2DComponent");

      moveFollowComponent->setIdToFollow(entityToFollow->getId());
      if (posToFollow == NULL)
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
