#include "Speed2DComponent.hh"

//----- ----- Constructors ----- ----- //
Speed2DComponent::Speed2DComponent(float x, float y)
  : AComponent("Speed2DComponent")
{
  this->_vX = x;
  this->_vY = y;
}

Speed2DComponent::Speed2DComponent(const Speed2DComponent &ref)
  : AComponent("Speed2DComponent")
{
  this->_vX = ref._vX;
  this->_vY = ref._vY;
}

//----- ----- Destructor ----- ----- //
Speed2DComponent::~Speed2DComponent()
{}

//----- ----- Operators ----- ----- //
Speed2DComponent	&Speed2DComponent::operator=(const Speed2DComponent &ref)
{
  this->_vX = ref._vX;
  this->_vY = ref._vY;
  return (*this);
}

//----- ----- Getters ----- ----- //
float	Speed2DComponent::getVX() const
{
  return (this->_vX);
}

float	Speed2DComponent::getVY() const
{
  return (this->_vY);
}

//----- ----- Setters ----- ----- //
void	Speed2DComponent::setVX(float x)
{
  this->_vX = x;
}

void	Speed2DComponent::setVY(float y)
{
  this->_vY = y;
}

void	Speed2DComponent::addVX(float x)
{
  this->_vX += x;
}

void	Speed2DComponent::addVY(float y)
{
  this->_vY += y;
}

void	Speed2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_vX;
  buffer << this->_vY;
}

void	Speed2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_vX;
  buffer >> this->_vY;
}
