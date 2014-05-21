#ifndef COLLISIONCOMPONENT_H_
# define COLLISIONCOMPONENT_H_

# include <list>

# include "AComponent.hpp"
# include "CollisionPoint.hh"

class CollisionComponent : public AComponent<CollisionComponent>
{

protected:
  std::list<CollisionPoint *>	_collisionPoints;

public:
  CollisionComponent();
  virtual	~CollisionComponent();
  CollisionComponent(const CollisionComponent&);
  CollisionComponent	&operator=(const CollisionComponent&);

  std::list<CollisionPoint *>	const &getCollisionPoints() const;
  CollisionComponent		*addCollisionPoint(CollisionPoint *);

};

#endif /* !COLLISIONCOMPONENT_H_ */
