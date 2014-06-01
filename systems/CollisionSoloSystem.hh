#ifndef COLLISIONSOLOSYSTEM_H_
# define COLLISIONSOLOSYSTEM_H_

# include "ASystem.hh"
# include "CollisionComponent.hh"
# include "QuadTree.hh"

class CollisionSoloSystem : public ASystem
{
public:
		CollisionSoloSystem();
  virtual	~CollisionSoloSystem();

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);

  virtual void		beforeProcess(const float);
  virtual void		afterProcess(const float);
protected:
  bool		isColliding(Pos2DComponent const &pos1, Box2DComponent const &box1,
			    Pos2DComponent const &pos2, Box2DComponent const &box2) const;

  bool		isCollidingAny(std::list<CollisionPoint *> const &Fpoints,
			       std::list<CollisionPoint *> const &Lpoints,
			       Pos2DComponent *posF, Pos2DComponent *posL);

  QuadTree	*quadTree;

};

#endif /* !COLLISIONSOLOSYSTEM_H_ */
