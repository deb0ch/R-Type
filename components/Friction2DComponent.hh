#ifndef FRICTION2DCOMPONENT_H_
# define FRICTION2DCOMPONENT_H_

# include	"AComponent.hh"

class		Friction2DComponent : public AComponent
{
public:
  float	getFrictionCoef() const;
  void	setFrictionCoef(float coef);

public:
		Friction2DComponent(float);
		Friction2DComponent(const Friction2DComponent&);
  virtual	~Friction2DComponent();
  Friction2DComponent	&operator=(const Friction2DComponent&);

protected:
  float		_frictionCoef;
};

#endif /* !FRICTION2DCOMPONENT_H_ */
