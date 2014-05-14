#ifndef MOVEFOLLOWCOMPONENT_H_
# define MOVEFOLLOWCOMPONENT_H_

# include	"AComponent.hpp"
# include	"Entity.hh"
# include	"World.hh"

class		MoveFollowComponent : public AComponent<MoveFollowComponent>
{
protected:
  unsigned long _idToFollow;

public:
		MoveFollowComponent(const unsigned long idToFollow = 0);
		MoveFollowComponent(const MoveFollowComponent&);
  virtual	~MoveFollowComponent();
  MoveFollowComponent	&operator=(const MoveFollowComponent&);

  /*
  float		getX() const;
  float		getY() const;
  */

  unsigned long	getIdToFollow() const;
  void		setIdToFollow(const unsigned long idToFollow);

};

#endif /* !MOVEFOLLOWCOMPONENT_H_ */
