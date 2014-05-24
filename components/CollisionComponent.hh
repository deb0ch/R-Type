#ifndef COLLISIONCOMPONENT_H_
# define COLLISIONCOMPONENT_H_

# include <list>

# include "AComponent.hpp"
# include "CollisionPoint.hh"

class CollisionComponent : public AComponent<CollisionComponent>
{

protected:
  std::list<CollisionPoint *>	_collisionPoints;
  std::list<std::string>	_toCollide;
  std::list<std::string>	_toNotCollide;

public:
  CollisionComponent();
  virtual	~CollisionComponent();
  CollisionComponent(const CollisionComponent&);
  CollisionComponent	&operator=(const CollisionComponent&);

  std::list<CollisionPoint *>	const &getCollisionPoints() const;
  CollisionComponent		*addCollisionPoint(CollisionPoint *);

  std::list<std::string>	const &getToCollide() const;
  std::list<std::string>	const &getToNotCollide() const;

  CollisionComponent	       *addToCollideItem(std::string const &);
  CollisionComponent	       *addNotToCollideItem(std::string const &);
};

#endif /* !COLLISIONCOMPONENT_H_ */
