#ifndef MOVEFOLLOWSYSTEM_H_
# define MOVEFOLLOWSYSTEM_H_

# include <math.h>
# include <vector>
# include "ASystem.hh"

#include "MoveFollowComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"
#include "TagComponent.hh"

class MoveFollowSystem : public ASystem
{
public:
		MoveFollowSystem();
  virtual	~MoveFollowSystem();
  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float);

private:
  inline float	getDistance(Pos2DComponent* a, Pos2DComponent* b) const;
  inline bool	isCloser(Pos2DComponent* follower,
			 Pos2DComponent* prevTarget,
			 Pos2DComponent* newTarget) const;
  Entity*	searchClosestTarget(Entity*, const std::string &) const;
};

#endif /* !MOVEFOLLOWSYSTEM_H_ */
