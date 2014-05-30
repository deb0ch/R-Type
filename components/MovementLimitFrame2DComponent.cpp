#include "MovementLimitFrame2DComponent.hh"

MovementLimitFrame2DComponent::MovementLimitFrame2DComponent(float posX, float posY,
							     float width, float height)
  : ACopyableComponent("MovementLimitFrame2DComponent")
{
  this->_posX = posX;
  this->_posY = posY;
  this->_width = width;
  this->_height = height;
}

MovementLimitFrame2DComponent::~MovementLimitFrame2DComponent() {}

MovementLimitFrame2DComponent::MovementLimitFrame2DComponent(const MovementLimitFrame2DComponent &e)
  : ACopyableComponent("MovementLimitFrame2DComponent")
{
  this->_posX = e._posX;
  this->_posY = e._posY;
  this->_width = e._width;
  this->_height = e._height;
}

MovementLimitFrame2DComponent	&MovementLimitFrame2DComponent::operator=(const MovementLimitFrame2DComponent &e)
{
  if (this != &e)
    {
      this->_posX = e._posX;
      this->_posY = e._posY;
      this->_width = e._width;
      this->_height = e._height;
    }
  return (*this);
}

float		MovementLimitFrame2DComponent::getPosX() const
{
  return (this->_posX);
}

float		MovementLimitFrame2DComponent::getPosY() const
{
  return (this->_posY);
}

float		MovementLimitFrame2DComponent::getWidth() const
{
  return (this->_width);
}

float		MovementLimitFrame2DComponent::getHeight() const
{
  return (this->_height);
}

void	MovementLimitFrame2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_posX;
  buffer << this->_posY;
  buffer << this->_width;
  buffer << this->_height;
}

void	MovementLimitFrame2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_posX;
  buffer >> this->_posY;
  buffer >> this->_width;
  buffer >> this->_height;
}

void	MovementLimitFrame2DComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("posX=.+")))
    this->_posX = std::stof(lastline.substr(5));
  else if (std::regex_match(lastline, std::regex("posY=.+")))
    this->_posY= std::stof(lastline.substr(5));
  else if (std::regex_match(lastline, std::regex("width=.+")))
    this->_width = std::stof(lastline.substr(6));
  else if (std::regex_match(lastline, std::regex("height=.+")))
    this->_height = std::stof(lastline.substr(7));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	MovementLimitFrame2DComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "posX=" << this->_posX << std::endl;
  output << std::string(indent, '\t') << "posY=" << this->_posY << std::endl;
  output << std::string(indent, '\t') << "width=" << this->_width << std::endl;
  output << std::string(indent, '\t') << "height=" << this->_height << std::endl;
}
