#include "SFMLInputComponent.hh"
#include	<iostream>
SFMLInputComponent::SFMLInputComponent()
  : AComponent("SFMLInputComponent")
{
  this->_inputs[sf::Keyboard::Key::Left] = "LEFT";
  this->_inputs[sf::Keyboard::Key::Right] = "RIGHT";
  this->_inputs[sf::Keyboard::Key::Down] = "DOWN";
  this->_inputs[sf::Keyboard::Key::Up] = "UP";
  this->_inputs[sf::Keyboard::Key::Space] = "UP";
  this->_inputs[sf::Keyboard::Key::U] = "UP";
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
