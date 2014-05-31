#ifndef		SFMLINPUTSYSTEM_H_
# define	SFMLINPUTSYSTEM_H_

# include	"SFML/Graphics.hpp"
# include	"SFML/Window/Keyboard.hpp"

# include	"ASystem.hh"
# include	"SFMLJoystickEvent.hh"

class		SFMLInputSystem : public ASystem
{
protected:
  sf::RenderWindow*			*_window;
  std::map<sf::Keyboard::Key, bool>	_inputs;
  std::map<unsigned int, bool>	_inputsJoystick;

  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);

public:
  SFMLInputSystem();
  virtual	~SFMLInputSystem();

  virtual void	init();

  void		SFMLKeyEventListener(IEvent *);
  void		SFMLJoystickEventListener(IEvent * ievent);
};

#endif /* !SFMLINPUTSYSTEM_H_ */
