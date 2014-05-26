#ifndef FRICTION2DCOMPONENT_H_
# define FRICTION2DCOMPONENT_H_

# include "ACopyableComponent.hpp"

class		Friction2DComponent : public ACopyableComponent<Friction2DComponent>
{
public:
  float		getFrictionCoef() const;
  void		setFrictionCoef(float coef);

public:
		Friction2DComponent(float coef = 0.01);
  virtual	~Friction2DComponent();

  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);

protected:
  float		_frictionCoef;
};

#endif /* !FRICTION2DCOMPONENT_H_ */
