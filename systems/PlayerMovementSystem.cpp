#include "PlayerMovementSystem.hh"
#include "PlayerMovementComponent.hh"

PlayerMovementSystem::PlayerMovementSystem() : ASystem("PlayerMovementSystem")
{

}

PlayerMovementSystem::~PlayerMovementSystem()
{

}

bool PlayerMovementSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("PlayerMovementComponent") && entity->hasComponent("SFMLInputComponent"))
    return (true);
  return (false);
}

void PlayerMovementSystem::processEntity(Entity *entity)
{
  SFMLInputComponent	*input;

  entity->getComponent<SFMLInputComponent>("SFMLInputComponent");
}
