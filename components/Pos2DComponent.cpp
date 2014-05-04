#include "Pos2DComponent.hh"
#include "Serializer.hpp"

//----- ----- Constructors ----- ----- //
Pos2DComponent::Pos2DComponent(float x, float y)
  : AComponent("Pos2DComponent")
{
  this->_x = x;
  this->_y = y;
}

Pos2DComponent::Pos2DComponent(const Pos2DComponent &ref)
  : AComponent("Pos2DComponent")
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

std::string	Pos2DComponent::serialize() const
{
  std::string	buffer;

  Serializer<float>::serialize(buffer, this->_x);
  Serializer<float>::serialize(buffer, this->_y);
  return (buffer);
}
