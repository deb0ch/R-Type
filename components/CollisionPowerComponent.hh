#ifndef COLLISIONPOWERCOMPONENT_H_
# define COLLISIONPOWERCOMPONENT_H_

# include	"ACopyableComponent.hpp"

class		CollisionPowerComponent : public ACopyableComponent<CollisionPowerComponent>
{
public:
	CollisionPowerComponent(unsigned int collisionPower = 100);
	virtual	~CollisionPowerComponent();
	virtual void	serialize(IBuffer &) const;
	virtual void	unserialize(IBuffer &);

	unsigned int	getCollisionPower() const;

	void setCollisionPower(const unsigned int collisionPower);

protected:
	unsigned int _collisionPower;
};

#endif /* !COLLISIONPOWERCOMPONENT_H_ */
