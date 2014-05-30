#include "Box2DComponent.hh"

Box2DComponent::Box2DComponent(float width, float height) : ACopyableComponent("Box2DComponent")
{
  this->_width = width;
  this->_height = height;
}

Box2DComponent::~Box2DComponent()
{

}

float		Box2DComponent::getWidth() const
{
  return (this->_width);
}

float		Box2DComponent::getHeight() const
{
  return (this->_height);
}

void		Box2DComponent::setWidth(float width)
{
  this->_width = width;
}

void		Box2DComponent::setHeight(float height)
{
  this->_height = height;
}

void	Box2DComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_width;
  buffer << this->_height;
}

void	Box2DComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_width;
  buffer >> this->_height;
}

void	Box2DComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("width=.+")))
    this->_width = std::stof(lastline.substr(6));
  else if (std::regex_match(lastline, std::regex("height=.+")))
    this->_height = std::stof(lastline.substr(7));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	Box2DComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "width=" << this->_width << std::endl;
  output << std::string(indent, '\t') << "height=" << this->_height << std::endl;
}
