#include "Box2DComponent.hh"

Box2DComponent::Box2DComponent() : AComponent("Box2DComponent")
{
  this->_width = 1.f;
  this->_height = 1.f;
}

Box2DComponent::~Box2DComponent()
{

}

Box2DComponent::Box2DComponent(const Box2DComponent &e) : AComponent("Box2DComponent")
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
