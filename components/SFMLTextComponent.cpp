#include <iostream>
#include "SFMLTextComponent.hh"

SFMLTextComponent::SFMLTextComponent(const std::string &text)
  : ACopyableComponent("SFMLTextComponent")
{
  this->_text = text;
}

SFMLTextComponent::~SFMLTextComponent() {

}

const std::string &SFMLTextComponent::getText() const {
  return this->_text;
}

void SFMLTextComponent::serialize(IBuffer &buffer) const {
  buffer << this->_text;
}

void SFMLTextComponent::unserialize(IBuffer &buffer) {
  buffer << this->_text;
}
