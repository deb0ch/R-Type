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

void SFMLTextComponent::setText(const std::string &text) {
  this->_text = text;
}

void SFMLTextComponent::serialize(IBuffer &buffer) const {
  buffer << this->_text;
}

void SFMLTextComponent::unserialize(IBuffer &buffer) {
  buffer >> this->_text;
}

void	SFMLTextComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("text=.+")))
    this->_text = lastline.substr(5);
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void		SFMLTextComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "text=" << this->_text << std::endl;
}
