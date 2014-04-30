#include "AComponent.hh"

AComponent::AComponent(const std::string &type)
{
  this->_type = type;
}

AComponent::~AComponent()
{
}

const std::string &AComponent::getType() const
{
  return (this->_type);
}
