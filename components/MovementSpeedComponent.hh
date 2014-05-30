#ifndef MOVEMENTSPEEDCOMPONENT_H_
# define MOVEMENTSPEEDCOMPONENT_H_

# include "ACopyableComponent.hpp"

class MovementSpeedComponent : public ACopyableComponent<MovementSpeedComponent>
{
public:
		MovementSpeedComponent(float movement_speed = 1.f);
  virtual	~MovementSpeedComponent();

  void		setSpeed(float);
  float		getSpeed() const;

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  float		_movement_speed;
};

#endif /* !MOVEMENTSPEEDCOMPONENT_H_ */
