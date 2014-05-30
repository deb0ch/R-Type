#include "CollisionPowerComponent.hh"

CollisionPowerComponent::CollisionPowerComponent(unsigned int collisionPower)
: ACopyableComponent("CollisionPowerComponent")
{
	this->_collisionPower = collisionPower;
}

CollisionPowerComponent::~CollisionPowerComponent()
{}

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

void	CollisionPowerComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "collisionPower=" << this->_collisionPower << std::endl;
}
