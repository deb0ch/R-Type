#ifndef SPEED2DCOMPONENT_H_
# define SPEED2DCOMPONENT_H_

# include	"AComponent.hh"

class		Speed2DComponent : public AComponent
{
protected:
  float		_vX;
  float		_vY;

public:
		Speed2DComponent(float x = 0.0f, float y = 0.0f);
		Speed2DComponent(const Speed2DComponent&);
  virtual	~Speed2DComponent();
  Speed2DComponent	&operator=(const Speed2DComponent&);

  float		getVX() const;
  float		getVY() const;

  void		setVX(float x);
  void		setVY(float y);
};

#endif /* !SPEED2DCOMPONENT_H_ */
