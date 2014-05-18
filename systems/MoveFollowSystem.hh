#ifndef MOVEFOLLOWSYSTEM_H_
# define MOVEFOLLOWSYSTEM_H_

# include <vector>
# include "ASystem.hh"

class MoveFollowSystem : public ASystem
{
private:
  std::vector<Entity *> _deletedElements;

public:
  MoveFollowSystem();
  virtual ~MoveFollowSystem();
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *, const float);
  virtual void init();

protected:
  virtual void		afterProcess();

private:
  void removeMoveFollowSystem(IEvent *event);

};

#endif /* !MOVEFOLLOWSYSTEM_H_ */
