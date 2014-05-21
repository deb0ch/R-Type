#ifndef MOVEMENTLIMITFRAME2DCOMPONENT_H_
# define MOVEMENTLIMITFRAME2DCOMPONENT_H_

# include "World.hh"
# include "AComponent.hpp"
# include "INetworkSerializableComponent.hh"

class MovementLimitFrame2DComponent : public AComponent<MovementLimitFrame2DComponent>,
				      public INetworkSerializableComponent
{
public:
  MovementLimitFrame2DComponent(float posX = 0.f, float posY = 0.f,
				float width = WINDOW_WIDTH, float height = WINDOW_HEIGHT);
  virtual	~MovementLimitFrame2DComponent();
  		MovementLimitFrame2DComponent(const MovementLimitFrame2DComponent&);
  MovementLimitFrame2DComponent	&operator=(const MovementLimitFrame2DComponent&);

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  float		getPosX() const;
  float		getPosY() const;
  float		getWidth() const;
  float		getHeight() const;

protected:
  float		_posX;
  float		_posY;
  float		_width;
  float		_height;
};

#endif /* !MOVEMENTLIMITFRAME2DCOMPONENT_H_ */