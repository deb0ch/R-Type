#ifndef COLLISIONCOMPONENT_H_
# define COLLISIONCOMPONENT_H_

# include <list>

# include "ASerializableComponent.hh"
# include "CollisionPoint.hh"

class CollisionComponent : public ASerializableComponent
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
  virtual ASerializableComponent	*cloneSerializable() const;
  virtual void				serialize(IBuffer &) const;
  virtual void				unserialize(IBuffer &);

  std::list<CollisionPoint *>	const &getCollisionPoints() const;
  CollisionComponent		*addCollisionPoint(CollisionPoint *);

  std::list<std::string>	const &getToCollide() const;
  std::list<std::string>	const &getToNotCollide() const;

  CollisionComponent	       *addToCollideItem(std::string const &);
  CollisionComponent	       *addNotToCollideItem(std::string const &);
};

#endif /* !COLLISIONCOMPONENT_H_ */
