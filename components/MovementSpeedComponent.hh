#ifndef MOVEMENTSPEEDCOMPONENT_H_
# define MOVEMENTSPEEDCOMPONENT_H_

# include "AComponent.hpp"
# include "ISerializableComponent.hh"
# include "INetworkSerializableComponent.hh"

class MovementSpeedComponent : public AComponent<MovementSpeedComponent>, public INetworkSerializableComponent
{
public:
		MovementSpeedComponent(float movement_speed = 1.f);
  virtual	~MovementSpeedComponent();

  void		setSpeed(float);
  float		getSpeed() const;

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

protected:
  float		_movement_speed;
};

#endif /* !MOVEMENTSPEEDCOMPONENT_H_ */
