#include "PlayerMovementSystem.hh"
#include "PlayerMovementComponent.hh"
#include "SFMLInputComponent.hh"
#include "Speed2DComponent.hh"
#include "MovementSpeedComponent.hh"

const std::map<sf::Keyboard::Key, std::pair<int, int> > PlayerMovementSystem::KeyMovement = {
  {sf::Keyboard::Left, {-1, 0}},
  {sf::Keyboard::Right, {1, 0}},
  {sf::Keyboard::Down, {0, 1}},
  {sf::Keyboard::Up, {0, -1}}
};

PlayerMovementSystem::PlayerMovementSystem() : ASystem("PlayerMovementSystem")
{}

PlayerMovementSystem::~PlayerMovementSystem()
{}

bool PlayerMovementSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("PlayerMovementComponent") && entity->hasComponent("SFMLInputComponent") &&
      entity->hasComponent("Speed2DComponent"))
    return (true);
  return (false);
}

void PlayerMovementSystem::processEntity(Entity *entity, const float)
{
  SFMLInputComponent		*input;
  Speed2DComponent		*speed;
  MovementSpeedComponent	*movement;
  float				mv_speed;

  input = entity->getComponent<SFMLInputComponent>("SFMLInputComponent");
  speed = entity->getComponent<Speed2DComponent>("Speed2DComponent");
  for (auto it = KeyMovement.begin(); it != KeyMovement.end(); ++it)
    {
      if ((movement = entity->getComponent<MovementSpeedComponent>("MovementSpeedComponent")))
	mv_speed = movement->getSpeed();
      else
	mv_speed = 1.f;
      if (input->isActived(it->first))
	{
	  speed->addVX(it->second.first * mv_speed);
	  speed->addVY(it->second.second * mv_speed);
	}
    }
}
