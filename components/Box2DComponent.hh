#ifndef BOX2DCOMPONENT_H_
# define BOX2DCOMPONENT_H_

# include "AComponent.hpp"

class Box2DComponent : public AComponent<Box2DComponent>
{
public:
  Box2DComponent(float width, float height);
  virtual	~Box2DComponent();
  		Box2DComponent(const Box2DComponent&);
  Box2DComponent	&operator=(const Box2DComponent&);



  float		getWidth() const;
  float		getHeight() const;
protected:
  float		_width;
  float		_height;
};

#endif /* !BOX2DCOMPONENT_H_ */
