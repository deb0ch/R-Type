#ifndef POWERUPCOMPONENT_H_
# define POWERUPCOMPONENT_H_

# include <string>
# include "ACopyableComponent.hpp"

class PowerUpComponent : public ACopyableComponent<PowerUpComponent>
{
public:
	PowerUpComponent(const std::string weapon = "");
	virtual	~PowerUpComponent();

	void	serialize(IBuffer &buffer) const;
	void	unserialize(IBuffer &buffer);

protected:
	std::string _newWeapon;

};

#endif /* !POWERUPCOMPONENT_H_ */
