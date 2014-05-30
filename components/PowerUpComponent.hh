#ifndef POWERUPCOMPONENT_H_
# define POWERUPCOMPONENT_H_

# include <string>
# include "ACopyableComponent.hpp"
# include "EntitySpawnerComponent.hh"

class PowerUpComponent : public ACopyableComponent<PowerUpComponent>
{
public:
	PowerUpComponent(const std::string weapon = "", float delay = 0.15f);
	virtual	~PowerUpComponent();

	void	upgrade(EntitySpawnerComponent *spawner);
	void	serialize(IBuffer &buffer) const;
	void	unserialize(IBuffer &buffer);

	virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
	std::string _newWeapon;
	float _newdelay;

};

#endif /* !POWERUPCOMPONENT_H_ */
