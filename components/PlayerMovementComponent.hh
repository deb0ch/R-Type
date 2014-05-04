#ifndef PLAYERMOVEMENTCOMPONENT_H_
# define PLAYERMOVEMENTCOMPONENT_H_

# include "AComponent.hpp"

class PlayerMovementComponent : public AComponent<PlayerMovementComponent>
{
public:
  PlayerMovementComponent() : AComponent("PlayerMovementComponent")
  {}

  virtual ~PlayerMovementComponent()
  {}
};

#endif /* !PLAYERMOVEMENTCOMPONENT_H_ */
