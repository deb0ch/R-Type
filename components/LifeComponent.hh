#ifndef LIFECOMPONENT_H_
# define LIFECOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		LifeComponent : public AComponent<LifeComponent>, public INetworkSerializableComponent
{
public:
	LifeComponent(unsigned int life = 100);
	LifeComponent(const LifeComponent&);
	virtual	~LifeComponent();
	LifeComponent	&operator=(const LifeComponent&);
	virtual void	serialize(IBuffer &) const;
	virtual void	unserialize(IBuffer &);

	unsigned int	getLife() const;
	void setLife(const unsigned int);

protected:
	unsigned int _life;
};

#endif /* !LIFECOMPONENT_H_ */