#include "Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
Pos2DComponent::Pos2DComponent(float x, float y)
  : ACopyableComponent("Pos2DComponent")
{
  this->_x = x;
  this->_y = y;
}

Pos2DComponent::Pos2DComponent(const Pos2DComponent &ref)
  : ACopyableComponent("Pos2DComponent")
{
  this->_x = ref._x;
  this->_y = ref._y;
}

//----- ----- Destructor ----- ----- //
Pos2DComponent::~Pos2DComponent()
{}

//----- ----- Operators ----- ----- //
Pos2DComponent	&Pos2DComponent::operator=(const Pos2DComponent &ref)
{
  this->_x = ref._x;
  this->_y = ref._y;
  return (*this);
}

//----- ----- Getters ----- ----- //
float	Pos2DComponent::getX() const
{
  return (this->_x);
}

float	Pos2DComponent::getY() const
{
  return (this->_y);
}

//----- ----- Setters ----- ----- //
void	Pos2DComponent::setX(float x)
{
  this->_x = x;
}

void	Pos2DComponent::setY(float y)
{
  this->_y = y;
}

void		Pos2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_x;
  buffer << this->_y;
}

void		Pos2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_x;
  buffer >> this->_y;
}
