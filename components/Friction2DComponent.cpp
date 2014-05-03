#include "Friction2DComponent.hh"

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
