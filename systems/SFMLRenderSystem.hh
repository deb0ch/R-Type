#ifndef SFMLRENDERSYSTEM_H_
# define SFMLRENDERSYSTEM_H_

# include		<SFML/Graphics.hpp>

# include		"ASystem.hh"

class			SFMLRenderSystem : public ASystem
{
protected:
  sf::RenderWindow	*_window;

  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
			SFMLRenderSystem();
  virtual		~SFMLRenderSystem();

  virtual void		start();
  virtual void		beforeProcess();
  virtual void		afterProcess();
};

#endif /* !SFMLRENDERSYSTEM_H_ */
