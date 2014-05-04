#ifndef MOVEMENTSPEEDCOMPONENT_H_
# define MOVEMENTSPEEDCOMPONENT_H_

# include "AComponent.hpp"

class MovementSpeedComponent : public AComponent<MovementSpeedComponent>
{
public:
		MovementSpeedComponent(float movement_speed = 1.f);
  virtual	~MovementSpeedComponent();

  void		setSpeed(float);
  float		getSpeed() const;

protected:
  float		_movement_speed;
};

#endif /* !MOVEMENTSPEEDCOMPONENT_H_ */
