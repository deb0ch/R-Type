#ifndef POWERUPSYSTEM_H_
# define POWERUPSYSTEM_H_

# include <vector>
# include <string>
# include "ASystem.hh"

class PowerUpSystem : public ASystem
{
public:
  PowerUpSystem(const std::vector<std::string> &, const std::vector<std::string> &);
	virtual ~PowerUpSystem();

	virtual void	init();
	void	collision_event(IEvent *);
	void	delete_entity(IEvent *);

protected:
	virtual bool canProcess(Entity *);
	virtual void processEntity(Entity *, const float);

	std::vector<std::string>	_possible_powerup;
	std::vector<std::string>	_powerup_component_names;
};


#endif /* !POWERUPSYSTEM_H_ */
