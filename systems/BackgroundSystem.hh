#ifndef BACKGROUNDSYSTEM_H_
# define BACKGROUNDSYSTEM_H_

# include "ASystem.hh"

class BackgroundSystem : public ASystem
{
public:
		BackgroundSystem();
  virtual	~BackgroundSystem();

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);
};

#endif /* !BACKGROUNDSYSTEM_H_ */
