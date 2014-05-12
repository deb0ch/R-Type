#ifndef BOX2DCOMPONENT_H_
# define BOX2DCOMPONENT_H_

# include "AComponent.hpp"
# include "INetworkSerializableComponent.hh"

class Box2DComponent : public AComponent<Box2DComponent>, public INetworkSerializableComponent
{
public:
  Box2DComponent(float width, float height);
  virtual	~Box2DComponent();
  		Box2DComponent(const Box2DComponent&);
  Box2DComponent	&operator=(const Box2DComponent&);

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  float		getWidth() const;
  float		getHeight() const;
protected:
  float		_width;
  float		_height;
};

#endif /* !BOX2DCOMPONENT_H_ */
