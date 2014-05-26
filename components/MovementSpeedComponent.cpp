#include "MovementSpeedComponent.hh"

MovementSpeedComponent::MovementSpeedComponent(float movement_speed) : ACopyableComponent("MovementSpeedComponent")
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

void	MovementSpeedComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_movement_speed;
}

void	MovementSpeedComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_movement_speed;
}
