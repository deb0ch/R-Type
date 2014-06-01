#ifndef		FIREALWAYSSYSTEM_H_
# define	FIREALWAYSSYSTEM_H_

# include	"ASystem.hh"

class		FireAlwaysSystem : public ASystem
{
public:
		FireAlwaysSystem();
  virtual	~FireAlwaysSystem();
  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float);
};

#endif		/* !FIREALWAYSSYSTEM_H_ */
