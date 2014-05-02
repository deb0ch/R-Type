#include "AComponent.hh"

//----- ----- Constructors ----- ----- //
AComponent::AComponent(const std::string &type)
{
  this->_type = type;
}

//----- ----- Destructor ----- ----- //
AComponent::~AComponent()
{}

//----- ----- Getters ----- ----- //
const std::string &AComponent::getType() const
{
  return (this->_type);
}
