#ifndef MOVEFOLLOWSYSTEM_H_
# define MOVEFOLLOWSYSTEM_H_

# include "ASystem.hh"

class MoveFollowSystem : public ASystem
{
public:
  MoveFollowSystem();
  virtual ~MoveFollowSystem();
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *, const float);
};

#endif /* !MOVEFOLLOWSYSTEM_H_ */
