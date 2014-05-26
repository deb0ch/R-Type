#ifndef MOVEFOLLOWCOMPONENT_H_
# define MOVEFOLLOWCOMPONENT_H_

# include	"Entity.hh"
# include	"ACopyableComponent.hpp"
# include	"World.hh"

class		MoveFollowComponent : public ACopyableComponent<MoveFollowComponent>
{
protected:
  unsigned int		_idToFollow;
  std::string		_tagToFollow;

public:
			MoveFollowComponent(const std::string & tagToFollow = "unknown");
  virtual		~MoveFollowComponent();

  virtual void		serialize(IBuffer &) const;
  virtual void		unserialize(IBuffer &);
  unsigned int		getIdToFollow() const;
  void			setIdToFollow(const unsigned int idToFollow);
  const std::string &	getTagToFollow() const;
  void			setTagToFollow(const std::string & idToFollow);
};

#endif /* !MOVEFOLLOWCOMPONENT_H_ */
