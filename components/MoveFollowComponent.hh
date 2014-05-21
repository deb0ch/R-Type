#ifndef MOVEFOLLOWCOMPONENT_H_
# define MOVEFOLLOWCOMPONENT_H_

# include	"AComponent.hpp"
# include	"Entity.hh"
# include	"World.hh"

class		MoveFollowComponent : public AComponent<MoveFollowComponent>
{
protected:
  unsigned long		_idToFollow;
  std::string		_tagToFollow;

public:
			MoveFollowComponent(const std::string & tagToFollow);
  virtual		~MoveFollowComponent();

  unsigned long		getIdToFollow() const;
  void			setIdToFollow(const unsigned long idToFollow);
  const std::string &	getTagToFollow() const;
  void			setTagToFollow(const std::string & idToFollow);
};

#endif /* !MOVEFOLLOWCOMPONENT_H_ */
