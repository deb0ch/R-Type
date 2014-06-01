#ifndef AUTODESTRUCTSYSTEM_H_
# define AUTODESTRUCTSYSTEM_H_

# include "ASystem.hh"

class AutoDestructSystem : public ASystem
{
public:
		AutoDestructSystem();
  virtual	~AutoDestructSystem();

  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float);
};

#endif /* !AUTODESTRUCTSYSTEM_H_ */
