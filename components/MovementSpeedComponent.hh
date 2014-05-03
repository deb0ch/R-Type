#ifndef MOVEMENTSPEEDCOMPONENT_H_
# define MOVEMENTSPEEDCOMPONENT_H_

# include "AComponent.hh"

class MovementSpeedComponent : public AComponent
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
