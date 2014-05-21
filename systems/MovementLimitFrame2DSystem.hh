#ifndef MOVEMENTLIMITFRAME2DSYSTEM_H_
# define MOVEMENTLIMITFRAME2DSYSTEM_H_

# include		"ASystem.hh"

class			MovementLimitFrame2DSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
  MovementLimitFrame2DSystem();
  virtual		~MovementLimitFrame2DSystem();
};

#endif /* !MOVEMENTLIMITFRAME2DSYSTEM_H_ */
