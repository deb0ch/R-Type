#include <iostream>
#include "CollisionSystem.hh"
#include "CollisionEvent.hh"

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

void	CollisionSystem::processEntity(Entity *entity, const float)
{
  std::vector<Entity *> &world_entities = this->_world->getEntities();
  Box2DComponent	*entity_box;
  Pos2DComponent	*entity_pos;
  Box2DComponent	*world_entity_box;
  Pos2DComponent	*world_entity_pos;

  entity_pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  entity_box = entity->getComponent<Box2DComponent>("Box2DComponent");
  for(auto it = world_entities.begin(); it != world_entities.end(); ++it)
    {
      world_entity_pos = (*it)->getComponent<Pos2DComponent>("Pos2DComponent");
      world_entity_box = (*it)->getComponent<Box2DComponent>("Box2DComponent");
      if (world_entity_pos && world_entity_box && *it != entity &&
	  isColliding(*entity_pos, *entity_box, *world_entity_pos, *world_entity_box))
	this->_world->sendEvent(new CollisionEvent(entity, *it));
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
  inner_right = std::min(pos1.getX() + (box1.getWidth() / 2.f),
			 pos2.getX() + (box2.getWidth() / 2.f));
  inner_top = std::max(pos1.getY() - (box1.getHeight() / 2.f),
		       pos2.getY() - (box2.getHeight() / 2.f));
  inner_bot = std::min(pos1.getY() + (box1.getHeight() / 2.f),
		       pos2.getY() + (box2.getHeight() / 2.f));
  return ((inner_left < inner_right) && (inner_top < inner_bot));
}

void	CollisionSystem::collision_event(IEvent *e)
{
  CollisionEvent*	event = dynamic_cast<CollisionEvent*>(e);
  std::cout << "Collision entre " <<   event->getEntity1()->getId() << " et " <<   event->getEntity2()->getId() << std::endl;
}
