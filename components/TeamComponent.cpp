#include <algorithm>
#include "TeamComponent.hh"

TeamComponent::TeamComponent(const unsigned int team) : ACopyableComponent("TeamComponent"){
  this->_team = team;
}

TeamComponent::~TeamComponent(){
}

void TeamComponent::setTeam(const unsigned int team) {
  this->_team = team;
}

unsigned int TeamComponent::getTeam() const {
  return this->_team;
}

void	TeamComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_team;
}

void	TeamComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_team;
}
