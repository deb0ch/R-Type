#include "Friction2DComponent.hh"

//----- ----- Constructors ----- ----- //
Friction2DComponent::Friction2DComponent(float coef)
  : ACopyableComponent("Friction2DComponent"), _frictionCoef(coef)
{}

Friction2DComponent::Friction2DComponent(const Friction2DComponent &ref)
  : ACopyableComponent("Friction2DComponent")
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

void	Friction2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_frictionCoef;
}

void	Friction2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_frictionCoef;
}
