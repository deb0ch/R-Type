#ifndef COLLISIONCOMPONENT_H_
# define COLLISIONCOMPONENT_H_

# include <list>

# include "ASerializableComponent.hh"
# include "CollisionPoint.hh"

class CollisionComponent : public ASerializableComponent
{

protected:
  std::list<CollisionPoint *>	_collisionPoints;

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

};

#endif /* !COLLISIONCOMPONENT_H_ */
