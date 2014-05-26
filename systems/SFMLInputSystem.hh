#ifndef		SFMLINPUTSYSTEM_H_
# define	SFMLINPUTSYSTEM_H_

# include	"SFML/Graphics.hpp"
# include	"SFML/Window/Keyboard.hpp"

# include	"ASystem.hh"

class		SFMLInputSystem : public ASystem
{
protected:
  sf::RenderWindow*			*_window;
  std::map<sf::Keyboard::Key, bool>	_inputs;

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);

public:
  SFMLInputSystem();
  virtual	~SFMLInputSystem();

  virtual void	init();

  void		SFMLKeyEventListener(IEvent *);
};

#endif /* !SFMLINPUTSYSTEM_H_ */
