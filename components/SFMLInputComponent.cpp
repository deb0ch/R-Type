#include "SFMLInputComponent.hh"

SFMLInputComponent::SFMLInputComponent()
  : AComponent("SFMLInputComponent")
{
  this->_inputs[sf::Keyboard::Left] = false;
  this->_inputs[sf::Keyboard::Right] = false;
  this->_inputs[sf::Keyboard::Down] = false;
  this->_inputs[sf::Keyboard::Up] = false;
  this->_inputs[sf::Keyboard::Space] = false;
}

SFMLInputComponent::~SFMLInputComponent()
{}

const std::map<sf::Keyboard::Key, bool> SFMLInputComponent::getInputs() const {
  return this->_inputs;
}

bool SFMLInputComponent::isActived(const sf::Keyboard::Key key) const {
  std::map<sf::Keyboard::Key, bool>::const_iterator it = this->_inputs.find(key);
  if (it != this->_inputs.end()) {
    return it->second;
  }
  return false;
}

void SFMLInputComponent::setStatusKey(const sf::Keyboard::Key key, const bool status) {
  std::map<sf::Keyboard::Key, bool>::const_iterator it = this->_inputs.find(key);
  if (it != this->_inputs.end()) {
    this->_inputs[key] = status;
  }
}
