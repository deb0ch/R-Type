#ifndef SFMLRENDERLIVESYSTEM_H_
# define SFMLRENDERLIVESYSTEM_H_

# include		"Pos2DComponent.hh"
# include		"ASystem.hh"

class			SFMLSetDisplayLiveSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
  SFMLSetDisplayLiveSystem();
  virtual		~SFMLSetDisplayLiveSystem();

};

#endif /* !SFMLRENDERLIVESYSTEM_H_ */
