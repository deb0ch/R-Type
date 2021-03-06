#include "ActionMovementSystem.hh"
#include "ActionComponent.hh"
#include "Speed2DComponent.hh"
#include "MovementSpeedComponent.hh"

const std::map<std::string, std::pair<int, int> > ActionMovementSystem::KeyMovement = {
  {"UP",	{0, -1}},
  {"LEFT",	{-1, 0}},
  {"DOWN",	{0, 1}},
  {"RIGHT",	{1, 0}}
};

ActionMovementSystem::ActionMovementSystem() : ASystem("ActionMovementSystem")
{}

ActionMovementSystem::~ActionMovementSystem()
{}

bool ActionMovementSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("ActionComponent") && entity->hasComponent("Speed2DComponent"))
    return (true);
  return (false);
}

void ActionMovementSystem::processEntity(Entity *entity, const float delta)
{
  ActionComponent		*action;
  Speed2DComponent		*speed;
  MovementSpeedComponent	*movement;
  float				mv_speed;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  speed = entity->getComponent<Speed2DComponent>("Speed2DComponent");

  if ((movement = entity->getComponent<MovementSpeedComponent>("MovementSpeedComponent")))
    mv_speed = movement->getSpeed();
  else
    mv_speed = 1.f;
  for (auto it = KeyMovement.begin(); it != KeyMovement.end(); ++it)
    {
      if (action->isActive(it->first))
	{
	  speed->addVX(it->second.first * mv_speed * delta);
	  speed->addVY(it->second.second * mv_speed * delta);
	}
    }
}
