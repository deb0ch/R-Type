#include "Window.hh"
#include "CollisionSoloSystem.hh"
#include "CollisionEvent.hh"
#include "TagComponent.hh"
#include "TeamComponent.hh"

CollisionSoloSystem::CollisionSoloSystem() : ASystem("CollisionSoloSystem", 40)
{
}

CollisionSoloSystem::~CollisionSoloSystem()
{
}

bool	CollisionSoloSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("CollisionComponent") &&
      entity->hasComponent("Pos2DComponent") &&
      entity->hasComponent("Box2DComponent"))
    return (true);
  return (false);
}

void		CollisionSoloSystem::beforeProcess(const float)
{
  if (World::QUADTREE)
    this->quadTree = new QuadTree(this->_world, this->_world->getEntities(), 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 4, 4);
}
void		CollisionSoloSystem::afterProcess(const float)
{
  if (World::QUADTREE)
    delete this->quadTree;
}

static bool	checkTags(TagComponent const *tags, CollisionComponent const *col)
{
  bool	collide, notCollide;

  collide = (tags) ? std::any_of(col->getToCollide().begin(), col->getToCollide().end(), [tags] (std::string tag) -> bool {return tags->hasTag(tag);}) : false;
  notCollide = (tags) ? std::any_of(col->getToNotCollide().begin(), col->getToNotCollide().end(), [tags] (std::string tag) -> bool {return tags->hasTag(tag);}) : false;
  if ((col->getToCollide().empty() && !notCollide) || (collide && !notCollide && !col->getToCollide().empty()))
    return (true);
  return (false);
}

void	CollisionSoloSystem::processEntity(Entity *entity, const float)
{
  CollisionComponent	*entity_col;
  CollisionComponent	*world_entity_col;
  TeamComponent		*entityTeam;
  TeamComponent		*worldEntityTeam;

  entity_col = entity->getComponent<CollisionComponent>("CollisionComponent");
  entityTeam = entity->getComponent<TeamComponent>("TeamComponent");
  if (!entity_col || !entityTeam)
    return ;
  std::vector<Entity *> const &entities = (World::QUADTREE) ? this->quadTree->findTree(entity) : this->_world->getEntities();
  for (auto it = entities.begin(); it != entities.end(); ++it)
    {
      world_entity_col = (*it)->getComponent<CollisionComponent>("CollisionComponent");
      worldEntityTeam = (*it)->getComponent<TeamComponent>("TeamComponent");
      if (world_entity_col && *it != entity &&
	  ((worldEntityTeam && worldEntityTeam->getTeam() != entityTeam->getTeam()) || !worldEntityTeam) &&
	  isCollidingAny(entity_col->getCollisionPoints(), world_entity_col->getCollisionPoints(),
	  entity->getComponent<Pos2DComponent>("Pos2DComponent"),
	  (*it)->getComponent<Pos2DComponent>("Pos2DComponent")) &&
	  checkTags((*it)->getComponent<TagComponent>("TagComponent"), entity_col))
	this->_world->sendEvent(new CollisionEvent(entity, *it));
    }
}

bool	CollisionSoloSystem::isCollidingAny(std::list<CollisionPoint *> const &Fpoints,
					std::list<CollisionPoint *> const &Lpoints,
					Pos2DComponent *posF, Pos2DComponent *posL)
{
  if (!posF || !posL)
    return (false);
  for (auto itF = Fpoints.begin(); itF != Fpoints.end(); ++itF)
    for (auto itL = Lpoints.begin(); itL != Lpoints.end(); ++itL)
      if (isColliding(*(*itF)->getPos() + *posF, *(*itF)->getBox(), *(*itL)->getPos() + *posL, *(*itL)->getBox()))
	return (true);
  return (false);
}

bool	CollisionSoloSystem::isColliding(Pos2DComponent const &pos1, Box2DComponent const &box1,
				     Pos2DComponent const &pos2, Box2DComponent const &box2) const
{
  float	inner_left;
  float	inner_right;
  float	inner_top;
  float	inner_bot;

  inner_left = (std::max)(pos1.getX() - (box1.getWidth() / 2.f),
			pos2.getX() - (box2.getWidth() / 2.f));
  inner_right = (std::min)(pos1.getX() + (box1.getWidth() / 2.f),
			 pos2.getX() + (box2.getWidth() / 2.f));
  inner_top = (std::max)(pos1.getY() - (box1.getHeight() / 2.f),
		       pos2.getY() - (box2.getHeight() / 2.f));
  inner_bot = (std::min)(pos1.getY() + (box1.getHeight() / 2.f),
		       pos2.getY() + (box2.getHeight() / 2.f));
  return ((inner_left < inner_right) && (inner_top < inner_bot));
}
