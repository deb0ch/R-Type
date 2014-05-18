#ifndef LIFECOMPONENT_H_
# define LIFECOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		LifeComponent : public AComponent<LifeComponent>, public INetworkSerializableComponent
{
public:
	LifeComponent(unsigned int life = 100, unsigned int invulnerability = 0);
	LifeComponent(const LifeComponent&);
	virtual	~LifeComponent();
	LifeComponent	&operator=(const LifeComponent&);
	virtual void	serialize(IBuffer &) const;
	virtual void	unserialize(IBuffer &);

	unsigned int	getLife() const;
	void decreaseLife(const unsigned int);
	void gainLife(const unsigned int);

	bool isInvulnerable() const;
	void decreaseInvulnerability();

protected:
	unsigned int _life;
	unsigned int _invulenerabilityMaxTime;
	unsigned int _invulnerability;
};

#endif /* !LIFECOMPONENT_H_ */