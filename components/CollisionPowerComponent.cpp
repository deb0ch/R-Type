#include "CollisionPowerComponent.hh"

CollisionPowerComponent::CollisionPowerComponent(unsigned int collisionPower)
: AComponent("CollisionPowerComponent")
{
	this->_collisionPower = collisionPower;
}

CollisionPowerComponent::CollisionPowerComponent(const CollisionPowerComponent &ref)
: AComponent("CollisionPowerComponent")
{
	this->_collisionPower = ref._collisionPower;
}


CollisionPowerComponent::~CollisionPowerComponent()
{}

//----- ----- Operators ----- ----- //
CollisionPowerComponent	&CollisionPowerComponent::operator=(const CollisionPowerComponent &ref)
{
	this->_collisionPower = ref._collisionPower;
	return (*this);
}

//----- ----- Getters ----- ----- //
unsigned int	CollisionPowerComponent::getCollisionPower() const
{
	return (this->_collisionPower);
}

void CollisionPowerComponent::setCollisionPower(const unsigned int collisionPower)
{
	this->_collisionPower = collisionPower;
}

void		CollisionPowerComponent::serialize(IBuffer &buffer) const
{
	buffer << this->_collisionPower;
}

void		CollisionPowerComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_collisionPower;
}
