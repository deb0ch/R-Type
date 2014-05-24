#include <iostream>
#include "CollisionSystem.hh"
#include "CollisionEvent.hh"
#include "TeamComponent.hh"

CollisionSystem::CollisionSystem() : ASystem("CollisionSystem")
{
}

CollisionSystem::~CollisionSystem()
{
}

bool	CollisionSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("CollisionComponent"))
    return (true);
  return (false);
}

void	CollisionSystem::processEntity(Entity *entity, const float)
{
  std::vector<Entity *> &world_entities = this->_world->getEntities();
  CollisionComponent	*entity_col;
  CollisionComponent	*world_entity_col;
  TeamComponent		*entityTeam;
  TeamComponent		*worldEntityTeam;

  entity_col = entity->getComponent<CollisionComponent>("CollisionComponent");
  entityTeam = entity->getComponent<TeamComponent>("TeamComponent");
  if (!entity_col || !entityTeam)
    return ;
  for (auto it = world_entities.begin(); it != world_entities.end(); ++it)
    {
      world_entity_col = (*it)->getComponent<CollisionComponent>("CollisionComponent");
      worldEntityTeam = (*it)->getComponent<TeamComponent>("TeamComponent");
      if (world_entity_col && *it != entity &&
	  worldEntityTeam && worldEntityTeam->getTeam() != entityTeam->getTeam() &&
	  isCollidingAny(entity_col->getCollisionPoints(), world_entity_col->getCollisionPoints(),
			 entity->getComponent<Pos2DComponent>("Pos2DComponent"),
			 (*it)->getComponent<Pos2DComponent>("Pos2DComponent")))
	this->_world->sendEvent(new CollisionEvent(entity, *it));
    }
}

bool	CollisionSystem::isCollidingAny(std::list<CollisionPoint *> const &Fpoints,
					std::list<CollisionPoint *> const &Lpoints,
					Pos2DComponent *posF, Pos2DComponent *posL)
{
  if (!posF || !posL)
    return (false);
  for (auto itF = Fpoints.begin(); itF != Fpoints.end(); ++itF)
    for (auto itL = Lpoints.begin(); itL != Lpoints.end(); ++itL)
      if (isColliding(*(*(*itF)->getPos() + *posF), *(*itF)->getBox(), *(*(*itL)->getPos() + *posL), *(*itL)->getBox()))
	return (true);
  return (false);
}

bool	CollisionSystem::isColliding(Pos2DComponent const &pos1, Box2DComponent const &box1,
				     Pos2DComponent const &pos2, Box2DComponent const &box2) const
{
  float	inner_left;
  float	inner_right;
  float	inner_top;
  float	inner_bot;

  inner_left = std::max(pos1.getX() - (box1.getWidth() / 2.f),
			pos2.getX() - (box2.getWidth() / 2.f));
  inner_right = std::min(pos1.getX() + (box1.getWidth() / 2.f),
			 pos2.getX() + (box2.getWidth() / 2.f));
  inner_top = std::max(pos1.getY() - (box1.getHeight() / 2.f),
		       pos2.getY() - (box2.getHeight() / 2.f));
  inner_bot = std::min(pos1.getY() + (box1.getHeight() / 2.f),
		       pos2.getY() + (box2.getHeight() / 2.f));
  return ((inner_left < inner_right) && (inner_top < inner_bot));
}
