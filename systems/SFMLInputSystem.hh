#ifndef SFMLINPUTSYSTEM_H_
# define SFMLINPUTSYSTEM_H_

# include		"ASystem.hh"

class			SFMLInputSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
  SFMLInputSystem();
  virtual		~SFMLInputSystem();

};


#endif /* !SFMLINPUTSYSTEM_H_ */
