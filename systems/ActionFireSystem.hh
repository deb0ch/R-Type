#ifndef		ACTIONFIRESYSTEM_H_
# define	ACTIONFIRESYSTEM_H_

# include	<map>
# include	"ASystem.hh"
# include	"SFML/Window/Keyboard.hpp"

class		ActionFireSystem : public ASystem
{
public:
		ActionFireSystem();
  virtual	~ActionFireSystem();
  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);
};

#endif		/* !ACTIONFIRESYSTEM_H_ */
