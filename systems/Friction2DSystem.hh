#ifndef			FRICTION2DSYSTEM_H_
# define		FRICTION2DSYSTEM_H_

# include		"ASystem.hh"

class			Friction2DSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
  Friction2DSystem();
  virtual		~Friction2DSystem();
};

#endif /* !FRICTION2DSYSTEM_H_ */
