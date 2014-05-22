#ifndef EXPLOSIONCOMPONENT_H_
# define EXPLOSIONCOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		ExplosionComponent : public AComponent<ExplosionComponent>
{
public:
	ExplosionComponent(const std::string &name = "EXPLOSION");
	virtual	~ExplosionComponent();

	const std::string &getExplosionEntityName() const;

protected:
	std::string _explosionEntityName;
};

#endif /* !EXPLOSIONCOMPONENT_H_ */
