#ifndef MOVEFORWARDSYSTEM_H_
# define MOVEFORWARDSYSTEM_H_

# include "ASystem.hh"

class MoveForwardSystem : public ASystem
{
public:
  MoveForwardSystem();
  virtual ~MoveForwardSystem();
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *, const float);
};

#endif /* !MOVEFORWARDSYSTEM_H_ */
