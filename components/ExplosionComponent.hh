#ifndef EXPLOSIONCOMPONENT_H_
# define EXPLOSIONCOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		ExplosionComponent : public AComponent<ExplosionComponent>
{
public:
	ExplosionComponent(const std::string &name = "EXPLOSION", float offsetX = 0.0f, float offsetY = 0.0f);
	virtual	~ExplosionComponent();

	const std::string &getExplosionEntityName() const;
	float getOffsetX() const;
	float getOffsetY() const;

protected:
	float _offsetX;
	float _offsetY;
	std::string _explosionEntityName;
};

#endif /* !EXPLOSIONCOMPONENT_H_ */
