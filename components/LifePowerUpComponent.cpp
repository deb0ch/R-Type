#include "LifePowerUpComponent.hh"
#include "PlayerLifeSystem.hh"

LifePowerUpComponent::LifePowerUpComponent(unsigned int nb_bonus)
  : APowerUpComponent("LifePowerUpComponent")
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

void	LifePowerUpComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("nb_bonus=.+")))
    this->_nb_bonus = std::stoul(lastline.substr(9));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	LifePowerUpComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "nb_bonus=" << this->_nb_bonus << std::endl;
}

ASerializableComponent	*LifePowerUpComponent::cloneSerializable() const
{
  return (new LifePowerUpComponent(*this));
}
