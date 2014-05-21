#ifndef POS2DCOMPONENT_H_
# define POS2DCOMPONENT_H_

# include	"AComponent.hpp"
# include	"ISerializableComponent.hh"
# include	"INetworkSerializableComponent.hh"

class		Pos2DComponent : public AComponent<Pos2DComponent>, public INetworkSerializableComponent
{
protected:
  float		_x;
  float		_y;

public:
		Pos2DComponent(float x = 0.0f, float y = 0.0f);
  virtual	~Pos2DComponent();
  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  float		getX() const;
  float		getY() const;

  void		setX(float x);
  void		setY(float y);
};

#endif /* !POS2DCOMPONENT_H_ */
