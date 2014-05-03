#ifndef PLAYERMOVEMENTCOMPONENT_H_
# define PLAYERMOVEMENTCOMPONENT_H_

# include "AComponent.hh"

class PlayerMovementComponent : public AComponent
{
public:
  PlayerMovementComponent() : AComponent("PlayerMovementComponent")
  {}

  virtual ~PlayerMovementComponent()
  {}
};

#endif /* !PLAYERMOVEMENTCOMPONENT_H_ */
