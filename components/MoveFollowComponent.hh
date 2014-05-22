#ifndef MOVEFOLLOWCOMPONENT_H_
# define MOVEFOLLOWCOMPONENT_H_

# include	"Entity.hh"
# include	"ACopyableComponent.hpp"

class		MoveFollowComponent : public ACopyableComponent<MoveFollowComponent>
{
protected:
  Entity	*_target;

public:
		MoveFollowComponent(Entity *);
		MoveFollowComponent(const MoveFollowComponent&);
  virtual	~MoveFollowComponent();
  MoveFollowComponent	&operator=(const MoveFollowComponent&);
  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  float		getX() const;
  float		getY() const;
};

#endif /* !MOVEFOLLOWCOMPONENT_H_ */
