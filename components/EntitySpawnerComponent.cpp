#include "EntitySpawnerComponent.hh"

//----- ----- Constructors ----- ----- //
EntitySpawnerComponent::EntitySpawnerComponent(float x, float y)
  : AComponent("EntitySpawnerComponent")
{
  this->_vX = x;
  this->_vY = y;
}

EntitySpawnerComponent::EntitySpawnerComponent(const EntitySpawnerComponent &ref)
  : AComponent("EntitySpawnerComponent")
{
  this->_vX = ref._vX;
  this->_vY = ref._vY;
}

//----- ----- Destructor ----- ----- //
EntitySpawnerComponent::~EntitySpawnerComponent()
{}

//----- ----- Operators ----- ----- //
EntitySpawnerComponent	&EntitySpawnerComponent::operator=(const EntitySpawnerComponent &ref)
{
  this->_vX = ref._vX;
  this->_vY = ref._vY;
  return (*this);
}

//----- ----- Getters ----- ----- //
float	EntitySpawnerComponent::getVX() const
{
  return (this->_vX);
}

float	EntitySpawnerComponent::getVY() const
{
  return (this->_vY);
}

//----- ----- Setters ----- ----- //
void	EntitySpawnerComponent::setVX(float x)
{
  this->_vX = x;
}

void	EntitySpawnerComponent::setVY(float y)
{
  this->_vY = y;
}

void	EntitySpawnerComponent::addVX(float x)
{
  this->_vX += x;
}

void	EntitySpawnerComponent::addVY(float y)
{
  this->_vY += y;
}

void	EntitySpawnerComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_vX;
  buffer << this->_vY;
}

void	EntitySpawnerComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_vX;
  buffer >> this->_vY;
}
