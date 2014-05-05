#include "Friction2DComponent.hh"
#include "Serializer.hpp"

//----- ----- Constructors ----- ----- //
Friction2DComponent::Friction2DComponent(float coef)
  : AComponent("Friction2DComponent"), _frictionCoef(coef)
{}

Friction2DComponent::Friction2DComponent(const Friction2DComponent &ref)
  : AComponent("Friction2DComponent")
{
  this->_frictionCoef = ref._frictionCoef;
}

//----- ----- Destructor ----- ----- //
Friction2DComponent::~Friction2DComponent()
{}

//----- ----- Operators ----- ----- //
Friction2DComponent	&Friction2DComponent::operator=(const Friction2DComponent &ref)
{
  this->_frictionCoef = ref._frictionCoef;
  return (*this);
}

//----- ----- Getters ----- ----- //
float	Friction2DComponent::getFrictionCoef() const
{
  return (this->_frictionCoef);
}

//----- ----- Setters ----- ----- //
void	Friction2DComponent::setFrictionCoef(float coef)
{
  this->_frictionCoef = coef;
}

int	Friction2DComponent::serialize(char *buffer, int lenght) const
{
  int		lenght_written;

  lenght_written = 0;
  lenght_written += Serializer<float>::serialize(buffer + lenght_written,
						 lenght - lenght_written, this->_frictionCoef);
  return (lenght_written);
}

int	Friction2DComponent::unserialize(const char *buffer, int lenght)
{
  int		lenght_read;

  lenght_read = 0;
  lenght_read += Serializer<float>::unserialize(buffer + lenght_read, lenght - lenght_read,
						this->_frictionCoef);
  return (lenght_read);
}
