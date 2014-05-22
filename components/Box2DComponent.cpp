#include "Box2DComponent.hh"

Box2DComponent::Box2DComponent(float width, float height) : ACopyableComponent("Box2DComponent")
{
  this->_width = width;
  this->_height = height;
}

Box2DComponent::~Box2DComponent()
{

}

Box2DComponent::Box2DComponent(const Box2DComponent &e) : ACopyableComponent("Box2DComponent")
{
  this->_width = e._width;
  this->_height = e._height;
}

Box2DComponent	&Box2DComponent::operator=(const Box2DComponent &e)
{
  if (this != &e)
    {
      this->_width = e._width;
      this->_height = e._height;
    }
  return (*this);
}

float		Box2DComponent::getWidth() const
{
  return (this->_width);
}

float		Box2DComponent::getHeight() const
{
  return (this->_height);
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
