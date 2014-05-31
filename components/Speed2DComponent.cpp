#include "Speed2DComponent.hh"

//----- ----- Constructors ----- ----- //
Speed2DComponent::Speed2DComponent(float x, float y)
  : ACopyableComponent("Speed2DComponent")
{
  this->_vX = x;
  this->_vY = y;
}

//----- ----- Destructor ----- ----- //
Speed2DComponent::~Speed2DComponent()
{}

//----- ----- Getters ----- ----- //
float	Speed2DComponent::getVX() const
{
  return (this->_vX);
}

float	Speed2DComponent::getVY() const
{
  return (this->_vY);
}

//----- ----- Setters ----- ----- //
void	Speed2DComponent::setVX(float x)
{
  this->_vX = x;
}

void	Speed2DComponent::setVY(float y)
{
  this->_vY = y;
}

void	Speed2DComponent::addVX(float x)
{
  this->_vX += x;
}

void	Speed2DComponent::addVY(float y)
{
  this->_vY += y;
}

void	Speed2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_vX;
  buffer << this->_vY;
}

void	Speed2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_vX;
  buffer >> this->_vY;
}

void	Speed2DComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("vx=.+")))
    this->_vX = std::stof(lastline.substr(3));
  else if (std::regex_match(lastline, std::regex("vy=.+")))
    this->_vY = std::stof(lastline.substr(3));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	Speed2DComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "vx=" << this->_vX << std::endl;
  output << std::string(indent, '\t') << "vy=" << this->_vY << std::endl;
}
