#ifndef FRICTION2DSYSTEM_H_
# define FRICTION2DSYSTEM_H_

# include "Friction2DComponent.hh"
# include "Speed2DComponent.hh"
# include "ASystem.hh"

class Friction2DSystem : public ASystem
{
public:
  Friction2DSystem();
  virtual		~Friction2DSystem();

protected:
  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float);

private:
  float			applyFriction(float oldSpeed, float friction, float delta);
};

#endif /* !FRICTION2DSYSTEM_H_ */
