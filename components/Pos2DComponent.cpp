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
  char		buffer[500];
  float		x;
  float		y;
  int		lenght = 0;
  int		lenght_read = 0;

  lenght += Serializer<float>::serialize(buffer + lenght, 500 - lenght, this->_x);
  lenght += Serializer<float>::serialize(buffer + lenght, 500 - lenght, this->_y);
  std::cout << "Serializing x: " << _x << " y: " << _y << std::endl;
  lenght_read += Serializer<float>::unserialize(buffer + lenght_read, lenght - lenght_read, x);
  lenght_read += Serializer<float>::unserialize(buffer + lenght_read, lenght - lenght_read, y);
  std::cout << "Unserialized x: " << x << " y: " << y << std::endl;
  return (buffer);
}
