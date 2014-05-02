#ifndef COLLISIONSYSTEM_H_
# define COLLISIONSYSTEM_H_

# include "ASystem.hh"
# include "Box2DComponent.hh"
# include "Pos2DComponent.hh"

class CollisionSystem : public ASystem
{
public:
		CollisionSystem();
  virtual	~CollisionSystem();

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *);
protected:
   bool		isColliding(const Pos2DComponent &pos1, const Box2DComponent &box1,
			    const Pos2DComponent &pos2, const Box2DComponent &box2) const;
};

#endif /* !COLLISIONSYSTEM_H_ */
