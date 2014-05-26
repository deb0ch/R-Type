#ifndef BOX2DCOMPONENT_H_
# define BOX2DCOMPONENT_H_

# include "ACopyableComponent.hpp"

class Box2DComponent : public ACopyableComponent<Box2DComponent>
{
public:
  Box2DComponent(float width = 0.0f, float height = 0.0f);
  virtual	~Box2DComponent();

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  float		getWidth() const;
  float		getHeight() const;
protected:
  float		_width;
  float		_height;
};

#endif /* !BOX2DCOMPONENT_H_ */
