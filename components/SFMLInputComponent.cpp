#include "SFMLInputComponent.hh"

SFMLInputComponent::SFMLInputComponent()
  : AComponent("SFMLInputComponent")
{
  this->_inputs[sf::Keyboard::Left] = "LEFT";
  this->_inputs[sf::Keyboard::Right] = "RIGHT";
  this->_inputs[sf::Keyboard::Down] = "DOWN";
  this->_inputs[sf::Keyboard::Up] = "UP";
  this->_inputs[sf::Keyboard::Space] = "FIRE";
}

SFMLInputComponent::~SFMLInputComponent()
{}

const std::map<sf::Keyboard::Key, std::string>&	SFMLInputComponent::getInputs() const
{
  return (this->_inputs);
}

const std::string&	SFMLInputComponent::getAction(const sf::Keyboard::Key key) const
{
  auto it = this->_inputs.find(key);
  if (it != this->_inputs.end())
    return (it->second);
  return ("");
}

void	SFMLInputComponent::setAction(const sf::Keyboard::Key key, const std::string &action)
{
  this->_inputs[key] = action;
}
