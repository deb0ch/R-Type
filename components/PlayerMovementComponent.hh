#ifndef PLAYERMOVEMENTCOMPONENT_H_
# define PLAYERMOVEMENTCOMPONENT_H_

# include "AComponent.hpp"
# include "ISerializableComponent.hh"
# include "INetworkSerializableComponent.hh"

class PlayerMovementComponent : public AComponent<PlayerMovementComponent>, public INetworkSerializableComponent
{
public:
  PlayerMovementComponent() : AComponent("PlayerMovementComponent")
  {}

  virtual ~PlayerMovementComponent()
  {}

  virtual void serialize(IBuffer &) const
  {}

  virtual void unserialize(IBuffer &)
  {}
};

#endif /* !PLAYERMOVEMENTCOMPONENT_H_ */
