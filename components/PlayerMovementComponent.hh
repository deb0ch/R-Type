#ifndef PLAYERMOVEMENTCOMPONENT_H_
# define PLAYERMOVEMENTCOMPONENT_H_

# include "ACopyableComponent.hpp"

class PlayerMovementComponent : public ACopyableComponent<PlayerMovementComponent>
{
public:
  PlayerMovementComponent() : ACopyableComponent("PlayerMovementComponent")
  {}

  virtual ~PlayerMovementComponent()
  {}

  virtual void serialize(IBuffer &) const
  {}

  virtual void unserialize(IBuffer &)
  {}
};

#endif /* !PLAYERMOVEMENTCOMPONENT_H_ */
