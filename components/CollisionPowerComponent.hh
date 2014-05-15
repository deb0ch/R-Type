#ifndef COLLISIONPOWERCOMPONENT_H_
# define COLLISIONPOWERCOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		CollisionPowerComponent : public AComponent<CollisionPowerComponent>, public INetworkSerializableComponent
{
public:
	CollisionPowerComponent(unsigned int collisionPower = 100);
	CollisionPowerComponent(const CollisionPowerComponent&);
	virtual	~CollisionPowerComponent();
	CollisionPowerComponent	&operator=(const CollisionPowerComponent&);
	virtual void	serialize(IBuffer &) const;
	virtual void	unserialize(IBuffer &);

	unsigned int	getCollisionPower() const;

	void setCollisionPower(const unsigned int collisionPower);

protected:
	unsigned int _collisionPower;
};

#endif /* !COLLISIONPOWERCOMPONENT_H_ */