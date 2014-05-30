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

void	MovementSpeedComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("speed_coef=.+")))
    this->_movement_speed = std::stof(lastline.substr(11));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	MovementSpeedComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "speed_coef=" << this->_movement_speed << std::endl;
}
