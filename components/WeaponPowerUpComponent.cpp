#include "WeaponPowerUpComponent.hh"

WeaponPowerUpComponent::WeaponPowerUpComponent(const std::string weapon, float delay)
  : APowerUpComponent()
{
  this->_newWeapon = weapon;
  this->_newdelay = delay;
}

WeaponPowerUpComponent::~WeaponPowerUpComponent()
{}

void	WeaponPowerUpComponent::upgrade(World *, Entity *entity)
{
  EntitySpawnerComponent *spawner;
  spawner = entity->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent");
  if (spawner)
    {
      spawner->clearEntities();
      spawner->addEntity(std::pair<std::string, unsigned int>(this->_newWeapon, 0));
      spawner->setDelay(this->_newdelay);
    }
}

void	WeaponPowerUpComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "weapon=" << this->_newWeapon << std::endl;
  output << std::string(indent, '\t') << "delay=" << this->_newdelay << std::endl;
}

IComponent	*WeaponPowerUpComponent::clone() const
{
  return (new WeaponPowerUpComponent(*this));
}
