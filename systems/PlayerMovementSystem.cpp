#include "PlayerMovementSystem.hh"
#include "PlayerMovementComponent.hh"
#include "SFMLInputComponent.hh"
#include "Speed2DComponent.hh"

const std::map<sf::Keyboard::Key, std::pair<float, float> > PlayerMovementSystem::KeyMovement = {
  {sf::Keyboard::Left, {-1, 0}},
  {sf::Keyboard::Right, {1, 0}},
  {sf::Keyboard::Down, {0, 1}},
  {sf::Keyboard::Up, {0, -1}}
};

PlayerMovementSystem::PlayerMovementSystem() : ASystem("PlayerMovementSystem")
{

}

PlayerMovementSystem::~PlayerMovementSystem()
{

}

bool PlayerMovementSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("PlayerMovementComponent") && entity->hasComponent("SFMLInputComponent") &&
      entity->hasComponent("Speed2DComponent"))
    return (true);
  return (false);
}

void PlayerMovementSystem::processEntity(Entity *entity, const float)
{
  SFMLInputComponent	*input;
  Speed2DComponent	*speed;

  input = entity->getComponent<SFMLInputComponent>("SFMLInputComponent");
  speed = entity->getComponent<Speed2DComponent>("Speed2DComponent");
  for (auto it = KeyMovement.begin(); it != KeyMovement.end(); ++it)
    {
      if (input->isActived(it->first))
	{
	  speed->addVX(it->second.first);
	  speed->addVY(it->second.second);
	}
    }
}
