#include "LifePowerUpComponent.hh"
#include "PlayerLifeSystem.hh"

LifePowerUpComponent::LifePowerUpComponent(unsigned int nb_bonus)
  : APowerUpComponent()
{
  this->_nb_bonus = nb_bonus;
}

LifePowerUpComponent::~LifePowerUpComponent()
{}

void	LifePowerUpComponent::upgrade(World *world, Entity *)
{
  PlayerLifeSystem *lifesystem;

  lifesystem = world->getSystem<PlayerLifeSystem>("PlayerLifeSystem");
  if (lifesystem)
    {
      lifesystem->setNbLives(lifesystem->getNbLives() + 1);
      std::cout << "YOU GAIN A NEW LIFE!" << std::endl;
    }
  else
    {
      std::cerr << "NO LIFE SYSTEM" << std::endl;
    }
}

void	LifePowerUpComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "nb_bonus=" << this->_nb_bonus << std::endl;
}

IComponent	*LifePowerUpComponent::clone() const
{
  return (new LifePowerUpComponent(*this));
}
