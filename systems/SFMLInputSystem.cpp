#include	<iostream>
#include	<map>

#include	"SFMLInputSystem.hh"
#include	"SFMLInputComponent.hh"


SFMLInputSystem::SFMLInputSystem()
  : ASystem("SFMLInputSystem")
{
  this->_inputs[sf::Keyboard::Left] = false;
  this->_inputs[sf::Keyboard::Right] = false;
  this->_inputs[sf::Keyboard::Down] = false;
  this->_inputs[sf::Keyboard::Up] = false;
  this->_inputs[sf::Keyboard::Space] = false;
}

SFMLInputSystem::~SFMLInputSystem()
{}

bool	SFMLInputSystem::canProcess(Entity *e) {
  if (e->hasComponent("SFMLInputComponent"))
    return (true);
  return (false);
}

void	SFMLInputSystem::beforeProcess()
{
  for (auto it = this->_inputs.begin(); it != this->_inputs.end(); ++it)
    if (sf::Keyboard::isKeyPressed(it->first))
      this->_inputs[it->first] = true;
    else
      this->_inputs[it->first] = false;
}

void	SFMLInputSystem::processEntity(Entity *e, const float)
{
  SFMLInputComponent *inputComp;

  if (!(inputComp = e->getComponent<SFMLInputComponent>("SFMLInputComponent")))
    return ;
  for (auto it = this->_inputs.begin(); it != this->_inputs.end(); ++it)
    inputComp->setStatusKey(it->first, it->second);
}
