#ifndef SFMLRENDERSYSTEM_H_
# define SFMLRENDERSYSTEM_H_

# include		"SFML/Graphics.hpp"
# include		"Pos2DComponent.hh"
# include		"Window.hh"
# include		"ASystem.hh"

class			SFMLRenderTextSystem : public ASystem
{
protected:
  static const bool	debug = false;

  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
			SFMLRenderTextSystem();
  virtual		~SFMLRenderTextSystem();

};

#endif /* !SFMLRENDERSYSTEM_H_ */
