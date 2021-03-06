#ifndef SFMLDISPLAYSYSTEM_H_
# define SFMLDISPLAYSYSTEM_H_

# include		"SFML/Graphics.hpp"

# include		"ASystem.hh"
# include		"Window.hh"

class			SFMLDisplaySystem : public ASystem
{
protected:

  sf::RenderWindow	*_window;

  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float);

public:
			SFMLDisplaySystem();
  virtual		~SFMLDisplaySystem();

  virtual void		start();
  virtual void		beforeProcess(const float);
  virtual void		afterProcess(const float);
};

#endif /* !SFMLDISPLAYSYSTEM_H_ */
