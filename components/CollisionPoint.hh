#ifndef COLLISIONPOINT_H_
# define COLLISIONPOINT_H_

# include "AComponent.hpp"
# include "Box2DComponent.hh"
# include "Pos2DComponent.hh"

class CollisionPoint : public AComponent<CollisionPoint>
{

protected:
  Pos2DComponent	*_pos;
  Box2DComponent	*_box;

public:
  CollisionPoint(float x, float y, float width, float height);
  virtual	~CollisionPoint();
  CollisionPoint(const CollisionPoint&);
  CollisionPoint	&operator=(const CollisionPoint&);

  Box2DComponent		*getBox() const;
  Pos2DComponent		*getPos() const;

};

#endif /* !COLLISIONPOINT_H_ */
