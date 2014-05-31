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

void	TeamComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("team=.+")))
    this->_team = std::stof(lastline.substr(5));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	TeamComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "team=" << this->_team << std::endl;
}
