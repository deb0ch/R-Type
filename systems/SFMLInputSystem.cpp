#include	<iostream>
#include	<map>

#include	"SFMLInputSystem.hh"
#include	"SFMLInputComponent.hh"


SFMLInputSystem::SFMLInputSystem()
  : ASystem("SFMLInputSystem")
{}

SFMLInputSystem::~SFMLInputSystem()
{}

bool		SFMLInputSystem::canProcess(Entity *e) {
  if (e->hasComponent("SFMLInputComponent"))
    return (true);
  return (false);
}

void	SFMLInputSystem::processEntity(Entity *e, const float)
{
  SFMLInputComponent *inputComp;
  std::map<sf::Keyboard::Key, bool> inputs;
  std::map<sf::Keyboard::Key, bool>::const_iterator it;

  if (!(inputComp = e->getComponent<SFMLInputComponent>("SFMLInputComponent")))
    return ;

  inputs = inputComp->getInputs();
  for (it = inputs.begin(); it != inputs.end(); ++it)
    {
      if (sf::Keyboard::isKeyPressed(it->first))
	inputComp->setStatusKey(it->first, true);
      else
	inputComp->setStatusKey(it->first, false);
    }
}
