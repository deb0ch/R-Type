#include "CollisionComponent.hh"

CollisionComponent::CollisionComponent() : ASerializableComponent("CollisionComponent")
{}

CollisionComponent::~CollisionComponent()
{
  this->_collisionPoints.clear();
}

CollisionComponent::CollisionComponent(const CollisionComponent &e) : ASerializableComponent("CollisionComponent")
{
  this->_collisionPoints = e._collisionPoints;
}

CollisionComponent	&CollisionComponent::operator=(const CollisionComponent &e)
{
  if (this != &e)
    this->_collisionPoints = e._collisionPoints;
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
