#include "CollisionPoint.hh"

CollisionPoint::CollisionPoint(float x, float y, float width, float height) : AComponent("CollisionPoint")
{
  this->_pos = new Pos2DComponent(x, y);
  this->_box = new Box2DComponent(width, height);
}

CollisionPoint::~CollisionPoint()
{
  delete this->_pos;
  delete this->_box;
}

CollisionPoint::CollisionPoint(const CollisionPoint &e) : AComponent("CollisionPoint")
{
  this->_pos = e._pos;
  this->_box = e._box;
}

CollisionPoint	&CollisionPoint::operator=(const CollisionPoint &e)
{
  if (this != &e)
    {
      this->_box = e._box;
      this->_pos = e._pos;
    }
  return (*this);
}

Pos2DComponent		*CollisionPoint::getPos() const
{
  return (this->_pos);
}

Box2DComponent		*CollisionPoint::getBox() const
{
  return (this->_box);
}
