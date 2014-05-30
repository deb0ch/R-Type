#ifndef POWERUPSYSTEM_H_
# define POWERUPSYSTEM_H_

# include "ASystem.hh"

class PowerUpSystem : public ASystem
{
public:
	PowerUpSystem();
	virtual ~PowerUpSystem();

	void	collision_event(IEvent *);

protected:
	virtual bool canProcess(Entity *);
	virtual void processEntity(Entity *, const float);

};


#endif /* !POWERUPSYSTEM_H_ */