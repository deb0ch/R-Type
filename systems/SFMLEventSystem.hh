#ifndef		SFMLEVENTSYSTEM_H_
# define	SFMLEVENTSYSTEM_H_

# include	"SFML/Graphics.hpp"
# include	"SFML/Window/Keyboard.hpp"

# include	"ASystem.hh"

class		SFMLEventSystem : public ASystem
{
protected:
  sf::RenderWindow	*_window;

  virtual void	beforeProcess(const float);
  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);

public:
  SFMLEventSystem();
  virtual	~SFMLEventSystem();

  virtual void	init();
};

#endif /* !SFMLEVENTSYSTEM_H_ */
