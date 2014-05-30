#include "Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
Pos2DComponent::Pos2DComponent(float x, float y)
  : ACopyableComponent("Pos2DComponent")
{
  this->_x = x;
  this->_y = y;
  this->setNetworkCanSendUpdate(false);
}

//----- ----- Destructor ----- ----- //
Pos2DComponent::~Pos2DComponent()
{}

//----- ----- Getters ----- ----- //
float	Pos2DComponent::getX() const
{
  return (this->_x);
}

float	Pos2DComponent::getY() const
{
  return (this->_y);
}

//----- ----- Setters ----- ----- //
void	Pos2DComponent::setX(float x)
{
  this->_x = x;
}

void	Pos2DComponent::setY(float y)
{
  this->_y = y;
}

void		Pos2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_x;
  buffer << this->_y;
}

void		Pos2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_x;
  buffer >> this->_y;
}

void		Pos2DComponent::additionalNetworkSerialize(IBuffer &buffer) const
{
  buffer << Hash()("SyncPos2DComponent");
  this->serialize(buffer);
}

Pos2DComponent	*Pos2DComponent::operator+(const Pos2DComponent &add)
{
  return (new Pos2DComponent(this->_x + add._x, this->_y + add._y));
}

void		Pos2DComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "x=" << this->_x << std::endl;
  output << std::string(indent, '\t') << "y=" << this->_y << std::endl;
}
