#include "PowerUpComponent.hh"

PowerUpComponent::PowerUpComponent(const std::string weapon, float delay)
: ACopyableComponent("PowerUpComponent")
{
	this->_newWeapon = weapon;
	this->_newdelay = delay;
}

PowerUpComponent::~PowerUpComponent()
{
}

void	PowerUpComponent::upgrade(EntitySpawnerComponent *spawner)
{
	spawner->clearEntities();
	spawner->addEntity(std::pair<std::string, unsigned int>(this->_newWeapon, 0));
	spawner->setDelay(this->_newdelay);
}

void	PowerUpComponent::serialize(IBuffer &buffer) const
{
	buffer << this->_newWeapon;
}

void	PowerUpComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_newWeapon;
}

void	PowerUpComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
	output << std::string(indent, '\t') << "weapon=" << this->_newWeapon << std::endl;
}
