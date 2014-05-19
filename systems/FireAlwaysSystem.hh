#ifndef		FIREALWAYSSYSTEM_H_
# define	FIREALWAYSSYSTEM_H_

# include	<map>
# include	"ASystem.hh"
# include	"SFML/Window/Keyboard.hpp"

class		FireAlwaysSystem : public ASystem
{
public:
		FireAlwaysSystem();
  virtual	~FireAlwaysSystem();
  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);
};

#endif		/* !FIREALWAYSSYSTEM_H_ */
