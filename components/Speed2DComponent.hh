#ifndef SPEED2DCOMPONENT_H_
# define SPEED2DCOMPONENT_H_

# include	"AComponent.hh"

class		Speed2DComponent : public AComponent
{
protected:
  float		_sX;
  float		_sY;

public:
		Speed2DComponent(float x = 0.0f, float y = 0.0f);
		Speed2DComponent(const Speed2DComponent&);
  virtual	~Speed2DComponent();
  Speed2DComponent	&operator=(const Speed2DComponent&);

  float		getX() const;
  float		getY() const;

  void		setSX(float x);
  void		setSY(float y);
};

#endif /* !SPEED2DCOMPONENT_H_ */
