#ifndef EXPLOSIONCOMPONENT_H_
# define EXPLOSIONCOMPONENT_H_

# include	"ACopyableComponent.hpp"

class		ExplosionComponent : public ACopyableComponent<ExplosionComponent>
{
public:
	ExplosionComponent(const std::string &name = "EXPLOSION", float offsetX = 0.0f, float offsetY = 0.0f);
	virtual	~ExplosionComponent();

	const std::string &getExplosionEntityName() const;
	float getOffsetX() const;
	float getOffsetY() const;
	virtual void serialize(IBuffer &) const;
	virtual void unserialize(IBuffer &);

  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
	float _offsetX;
	float _offsetY;
	std::string _explosionEntityName;
};

#endif /* !EXPLOSIONCOMPONENT_H_ */
