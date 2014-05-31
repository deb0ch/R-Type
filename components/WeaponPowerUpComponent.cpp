#include "WeaponPowerUpComponent.hh"

WeaponPowerUpComponent::WeaponPowerUpComponent(const std::string weapon, float delay)
  : APowerUpComponent("WeaponPowerUpComponent")
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

void	WeaponPowerUpComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("delay=.+")))
    this->_newdelay = std::stoul(lastline.substr(6));
  else if (std::regex_match(lastline, std::regex("weapon=.+")))
    this->_newWeapon = lastline.substr(7);
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	WeaponPowerUpComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "weapon=" << this->_newWeapon << std::endl;
  output << std::string(indent, '\t') << "delay=" << this->_newdelay << std::endl;
}

ASerializableComponent	*WeaponPowerUpComponent::cloneSerializable() const
{
  return (new WeaponPowerUpComponent(*this));
}
