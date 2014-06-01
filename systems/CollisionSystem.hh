#ifndef COLLISIONSYSTEM_H_
# define COLLISIONSYSTEM_H_

# include "ASystem.hh"
# include "CollisionComponent.hh"

class CollisionSystem : public ASystem
{
public:
		CollisionSystem();
  virtual	~CollisionSystem();

  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float);

protected:
  bool		isColliding(Pos2DComponent const &pos1, Box2DComponent const &box1,
			    Pos2DComponent const &pos2, Box2DComponent const &box2) const;

  bool		isCollidingAny(std::list<CollisionPoint *> const &Fpoints,
			       std::list<CollisionPoint *> const &Lpoints,
			       Pos2DComponent *posF, Pos2DComponent *posL);


};

#endif /* !COLLISIONSYSTEM_H_ */
