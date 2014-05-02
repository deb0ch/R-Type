#include "Speed2DComponent.hh"

//----- ----- Constructors ----- ----- //
Speed2DComponent::Speed2DComponent(float x, float y)
  : AComponent("Speed2DComponent")
{
  this->_sX = x;
  this->_sY = y;
}

Speed2DComponent::Speed2DComponent(const Speed2DComponent &ref)
  : AComponent("Speed2DComponent")
{
  this->_sX = ref._sX;
  this->_sY = ref._sY;
}

//----- ----- Destructor ----- ----- //
Speed2DComponent::~Speed2DComponent()
{}

//----- ----- Operators ----- ----- //
Speed2DComponent	&Speed2DComponent::operator=(const Speed2DComponent &ref)
{
  this->_sX = ref._sX;
  this->_sY = ref._sY;
  return (*this);
}

//----- ----- Getters ----- ----- //
float	Speed2DComponent::getX() const
{
  return (this->_sX);
}

float	Speed2DComponent::getY() const
{
  return (this->_sY);
}

//----- ----- Setters ----- ----- //
void	Speed2DComponent::setX(float x)
{
  this->_sX = x;
}

void	Speed2DComponent::setY(float y)
{
  this->_sY = y;
}
