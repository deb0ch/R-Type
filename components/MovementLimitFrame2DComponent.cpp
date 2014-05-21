#include "MovementLimitFrame2DComponent.hh"

MovementLimitFrame2DComponent::MovementLimitFrame2DComponent(float posX, float posY,
							     float width, float height)
  : AComponent("MovementLimitFrame2DComponent")
{
  this->_posX = posX;
  this->_posY = posY;
  this->_width = width;
  this->_height = height;
}

MovementLimitFrame2DComponent::~MovementLimitFrame2DComponent() {}

MovementLimitFrame2DComponent::MovementLimitFrame2DComponent(const MovementLimitFrame2DComponent &e)
  : AComponent("MovementLimitFrame2DComponent")
{
  this->_posX = e._posX;
  this->_posY = e._posY;
  this->_width = e._width;
  this->_height = e._height;
}

MovementLimitFrame2DComponent	&MovementLimitFrame2DComponent::operator=(const MovementLimitFrame2DComponent &e)
{
  if (this != &e)
    {
      this->_posX = e._posX;
      this->_posY = e._posY;
      this->_width = e._width;
      this->_height = e._height;
    }
  return (*this);
}

float		MovementLimitFrame2DComponent::getPosX() const
{
  return (this->_posX);
}

float		MovementLimitFrame2DComponent::getPosY() const
{
  return (this->_posY);
}

float		MovementLimitFrame2DComponent::getWidth() const
{
  return (this->_width);
}

float		MovementLimitFrame2DComponent::getHeight() const
{
  return (this->_height);
}

void	MovementLimitFrame2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_posX;
  buffer << this->_posY;
  buffer << this->_width;
  buffer << this->_height;
}

void	MovementLimitFrame2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_posX;
  buffer >> this->_posY;
  buffer >> this->_width;
  buffer >> this->_height;
}
