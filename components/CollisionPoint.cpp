#include "CollisionPoint.hh"

CollisionPoint::CollisionPoint(float x, float y, float width, float height) : ACopyableComponent("CollisionPoint")
{
  this->_pos = new Pos2DComponent(x, y);
  this->_box = new Box2DComponent(width, height);
}

CollisionPoint::~CollisionPoint()
{
  delete this->_pos;
  delete this->_box;
}

CollisionPoint::CollisionPoint(const CollisionPoint &e) : ACopyableComponent("CollisionPoint")
{
  if (e._pos)
    this->_pos = new Pos2DComponent(*e._pos);
  else
    this->_pos = NULL;
  if (e._box)
    this->_box = new Box2DComponent(*e._box);
  else
    this->_pos = NULL;
}

CollisionPoint	&CollisionPoint::operator=(const CollisionPoint &e)
{
  if (this != &e)
    {
      if (e._pos)
	this->_pos = new Pos2DComponent(*e._pos);
      else
	this->_pos = NULL;
      if (e._box)
	this->_box = new Box2DComponent(*e._box);
      else
	this->_pos = NULL;
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

void			CollisionPoint::serialize(IBuffer &) const
{}

void			CollisionPoint::unserialize(IBuffer &)
{}
