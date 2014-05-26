#include "CollisionComponent.hh"

CollisionComponent::CollisionComponent() : ASerializableComponent("CollisionComponent")
{}

CollisionComponent::~CollisionComponent()
{
  this->_collisionPoints.clear();
  this->_toCollide.clear();
  this->_toNotCollide.clear();
}

CollisionComponent::CollisionComponent(const CollisionComponent &e) : ASerializableComponent("CollisionComponent")
{
  this->_collisionPoints = e._collisionPoints;
  this->_toCollide = e._toCollide;
  this->_toNotCollide = e._toNotCollide;
}

CollisionComponent	&CollisionComponent::operator=(const CollisionComponent &e)
{
  if (this != &e)
    {
      this->_collisionPoints = e._collisionPoints;
      this->_toCollide = e._toCollide;
      this->_toNotCollide = e._toNotCollide;
    }
  return (*this);
}

std::list<CollisionPoint *>	const &CollisionComponent::getCollisionPoints() const
{
  return (this->_collisionPoints);
}

CollisionComponent		*CollisionComponent::addCollisionPoint(CollisionPoint *point)
{
  this->_collisionPoints.push_front(point);
  return (this);
}

ASerializableComponent		*CollisionComponent::cloneSerializable() const
{
  return (new CollisionComponent(*this));
}

void				CollisionComponent::serialize(IBuffer &) const
{}

void				CollisionComponent::unserialize(IBuffer &)
{}

std::list<std::string>	const &CollisionComponent::getToCollide() const
{
  return (this->_toCollide);
}

std::list<std::string>	const &CollisionComponent::getToNotCollide() const
{
  return (this->_toNotCollide);
}

CollisionComponent	       *CollisionComponent::addToCollideItem(std::string const &item)
{
  this->_toCollide.push_front(item);
  return (this);
}

CollisionComponent	       *CollisionComponent::addNotToCollideItem(std::string const &item)
{
  this->_toNotCollide.push_front(item);
  return (this);
}
