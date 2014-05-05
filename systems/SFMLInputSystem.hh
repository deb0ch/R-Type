#ifndef		SFMLINPUTSYSTEM_H_
# define	SFMLINPUTSYSTEM_H_

#include	"SFML/Window/Keyboard.hpp"

# include	"ASystem.hh"

class		SFMLInputSystem : public ASystem
{
protected:
  std::map<sf::Keyboard::Key, bool>	_inputs;

  virtual void	beforeProcess();
  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);

public:
  SFMLInputSystem();
  virtual	~SFMLInputSystem();
};

#endif /* !SFMLINPUTSYSTEM_H_ */
