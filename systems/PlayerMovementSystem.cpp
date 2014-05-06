#include "PlayerMovementSystem.hh"
#include "PlayerMovementComponent.hh"
#include "ActionComponent.hh"
#include "Speed2DComponent.hh"
#include "MovementSpeedComponent.hh"

const std::map<std::string, std::pair<int, int> > PlayerMovementSystem::KeyMovement = {
  {"LEFT",	{-1, 0}},
  {"RIGHT ",	{1, 0}},
  {"DOWN",	{0, 1}},
  {"UP",	{0, -1}}
};

PlayerMovementSystem::PlayerMovementSystem() : ASystem("PlayerMovementSystem")
{}

PlayerMovementSystem::~PlayerMovementSystem()
{}

bool PlayerMovementSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("ActionComponent") && entity->hasComponent("Speed2DComponent"))
    return (true);
  return (false);
}

void PlayerMovementSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action;
  Speed2DComponent		*speed;
  MovementSpeedComponent	*movement;
  float				mv_speed;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  speed = entity->getComponent<Speed2DComponent>("Speed2DComponent");
  for (auto it = KeyMovement.begin(); it != KeyMovement.end(); ++it)
    {
      if ((movement = entity->getComponent<MovementSpeedComponent>("MovementSpeedComponent")))
	mv_speed = movement->getSpeed();
      else
	mv_speed = 1.f;
      if (action->isActive(it->first))
	{
	  speed->addVX(it->second.first * mv_speed);
	  speed->addVY(it->second.second * mv_speed);
	}
    }
}
