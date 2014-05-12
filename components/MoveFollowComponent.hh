#ifndef MOVEFOLLOWCOMPONENT_H_
# define MOVEFOLLOWCOMPONENT_H_

# include	"AComponent.hpp"
# include	"Entity.hh"

class		MoveFollowComponent : public AComponent<MoveFollowComponent>
{
protected:
  Entity	*_target;

public:
		MoveFollowComponent(Entity *);
		MoveFollowComponent(const MoveFollowComponent&);
  virtual	~MoveFollowComponent();
  MoveFollowComponent	&operator=(const MoveFollowComponent&);

  float		getX() const;
  float		getY() const;
};

#endif /* !MOVEFOLLOWCOMPONENT_H_ */
