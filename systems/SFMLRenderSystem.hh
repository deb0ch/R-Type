#ifndef SFMLRENDERSYSTEM_H_
# define SFMLRENDERSYSTEM_H_

# include		"SFML/Graphics.hpp"
# include		"Pos2DComponent.hh"

# include		"ASystem.hh"

class			SFMLRenderSystem : public ASystem
{
protected:
  static const bool	debug = false;

  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
			SFMLRenderSystem();
  virtual		~SFMLRenderSystem();

  virtual void		start();
  virtual void		beforeProcess(const float);
  virtual void		afterProcess(const float);

  void			displayCollision(Entity *entity, sf::RenderWindow *);
  void			displayBox2D(float width, float height, Pos2DComponent *pos, sf::RenderWindow *);
};

#endif /* !SFMLRENDERSYSTEM_H_ */
