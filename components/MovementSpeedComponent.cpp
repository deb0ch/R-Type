#include "MovementSpeedComponent.hh"

MovementSpeedComponent::MovementSpeedComponent(float movement_speed) : AComponent("MovementSpeedComponent")
{
  this->_movement_speed = movement_speed;
}

MovementSpeedComponent::~MovementSpeedComponent()
{}

void	MovementSpeedComponent::setSpeed(float speed)
{
  this->_movement_speed = speed;
}

float	MovementSpeedComponent::getSpeed() const
{
  return (this->_movement_speed);
}
