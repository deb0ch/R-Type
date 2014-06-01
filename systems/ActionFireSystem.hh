#ifndef		ACTIONFIRESYSTEM_H_
# define	ACTIONFIRESYSTEM_H_

# include	"ASystem.hh"

class		ActionFireSystem : public ASystem
{
public:
		ActionFireSystem();
  virtual	~ActionFireSystem();
  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float);
};

#endif		/* !ACTIONFIRESYSTEM_H_ */
