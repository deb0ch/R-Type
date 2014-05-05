#ifndef FRICTION2DCOMPONENT_H_
# define FRICTION2DCOMPONENT_H_

# include	"AComponent.hpp"

class		Friction2DComponent : public AComponent<Friction2DComponent>
{
public:
  float	getFrictionCoef() const;
  void	setFrictionCoef(float coef);

public:
		Friction2DComponent(float coef = 0.01);
		Friction2DComponent(const Friction2DComponent&);
  virtual	~Friction2DComponent();
  Friction2DComponent	&operator=(const Friction2DComponent&);

protected:
  float		_frictionCoef;
};

#endif /* !FRICTION2DCOMPONENT_H_ */
