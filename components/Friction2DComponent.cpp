#include "Friction2DComponent.hh"

//----- ----- Constructors ----- ----- //
Friction2DComponent::Friction2DComponent(float coef)
  : AComponent("Friction2DComponent"), _frictionCoef(coef)
{}

//----- ----- Destructor ----- ----- //
Friction2DComponent::~Friction2DComponent()
{}

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
