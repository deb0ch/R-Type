#include "Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
Pos2DComponent::Pos2DComponent(float x, float y)
  : AComponent("Pos2DComponent")
{
  this->_x = x;
  this->_y = y;
}

//----- ----- Destructor ----- ----- //
Pos2DComponent::~Pos2DComponent()
{}

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
