#include "CollisionSystem.hh"

CollisionSystem::CollisionSystem() : ASystem("CollisionSystem")
{
}

CollisionSystem::~CollisionSystem()
{
}

bool	CollisionSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("Pos2DComponent") && entity->hasComponent("Box2DComponent"))
    return (true);
  return (false);
}

void	CollisionSystem::processEntity(Entity *entity)
{
  std::vector<Entity *> &world_entities = this->_world->getEntities();
  Box2DComponent	*entity_box;
  Pos2DComponent	*entity_pos;

  for(auto it = world_entities.begin(); it != world_entities.end(); ++it)
    {
      if (isColliding(*entity_pos, *entity_box,
		      *(*it)->hasComponent("Pos2DComponent"), *(*it)->hasComponent("Box2DComponent")))
	std::cout << "BADABOUM MODAFUCKA" << std::endl;
    }
}

bool	CollisionSystem::isColliding(const Pos2DComponent &pos1, const Box2DComponent &box1,
				     const Pos2DComponent &pos2, const Box2DComponent &box2) const
{
  float	inner_left;
  float	inner_right;
  float	inner_top;
  float	inner_bot;

  inner_left = std::max(pos1.getX() - (box1.getWidth() / 2.f),
			pos2.getX() - (box2.getWidth() / 2.f));
  inner_right = std::max(pos1.getX() + (box1.getWidth() / 2.f),
			 pos2.getX() + (box2.getWidth() / 2.f));
  inner_top = std::max(pos1.getY() - (box1.getHeight() / 2.f),
		       pos2.getY() - (box2.getHeight() / 2.f));
  inner_bot = std::max(pos1.getY() + (box1.getHeight() / 2.f),
		       pos2.getY() + (box2.getHeight() / 2.f));
  return ((inner_left < inner_right) && (inner_top < inner_bot));
}
