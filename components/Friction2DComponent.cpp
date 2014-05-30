#include "Friction2DComponent.hh"

//----- ----- Constructors ----- ----- //
Friction2DComponent::Friction2DComponent(float coef)
  : ACopyableComponent("Friction2DComponent"), _frictionCoef(coef)
{}

//----- ----- Destructor ----- ----- //
Friction2DComponent::~Friction2DComponent()
{}

//----- ----- Getters ----- ----- //
float	Friction2DComponent::getFrictionCoef() const
{
  return (this->_frictionCoef);
}

//----- ----- Setters ----- ----- //
void	Friction2DComponent::setFrictionCoef(float coef)
{
  this->_frictionCoef = coef;
}

void	Friction2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_frictionCoef;
}

void	Friction2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_frictionCoef;
}

void	Friction2DComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("coef=.+")))
    this->_frictionCoef = std::stof(lastline.substr(5));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	Friction2DComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "coef=" << this->_frictionCoef << std::endl;
}
