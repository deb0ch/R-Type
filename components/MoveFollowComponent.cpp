
#include	"MoveFollowComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveFollowComponent::MoveFollowComponent(const std::string & tagToFollow)
  : AComponent("MoveFollowComponent")
{
  this->_tagToFollow = tagToFollow;
}

//----- ----- Destructor ----- ----- //
MoveFollowComponent::~MoveFollowComponent()
{}

const std::string &	MoveFollowComponent::getTagToFollow() const
{
  return this->_tagToFollow;
}

void		MoveFollowComponent::setTagToFollow(const std::string & tagToFollow)
{
  this->_tagToFollow = tagToFollow;
}
