#ifndef SFMLDISPLAYSYSTEM_H_
# define SFMDISPLAYSYSTEM_H_

# include		"SFML/Graphics.hpp"

# include		"ASystem.hh"

class			SFMLDisplaySystem : public ASystem
{
protected:

  sf::RenderWindow	*_window;

  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
			SFMLDisplaySystem();
  virtual		~SFMLDisplaySystem();

  virtual void		start();
  virtual void		beforeProcess(const float);
  virtual void		afterProcess(const float);
};

#endif /* !SFMLDISPLAYSYSTEM_H_ */
