#include "PowerUpComponent.hh"

PowerUpComponent::PowerUpComponent(const std::string weapon)
: ACopyableComponent("PowerUpComponent")
{
	this->_newWeapon = weapon;
}

PowerUpComponent::~PowerUpComponent()
{
}

void	PowerUpComponent::serialize(IBuffer &buffer) const
{
	buffer << this->_newWeapon;
}

void	PowerUpComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_newWeapon;
}
