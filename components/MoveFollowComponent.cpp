
#include	"MoveFollowComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveFollowComponent::MoveFollowComponent(const std::string & tagToFollow)
  : ACopyableComponent("MoveFollowComponent"), _idToFollow(-1)
{
  this->_tagToFollow = tagToFollow;
}

//----- ----- Destructor ----- ----- //
MoveFollowComponent::~MoveFollowComponent()
{}

unsigned long	MoveFollowComponent::getIdToFollow() const
{
  return this->_idToFollow;
}

void		MoveFollowComponent::setIdToFollow(unsigned long idToFollow)
{
  this->_idToFollow = idToFollow;
}

const std::string &	MoveFollowComponent::getTagToFollow() const
{
  return this->_tagToFollow;
}

void		MoveFollowComponent::serialize(IBuffer &) const
{}

void		MoveFollowComponent::unserialize(IBuffer &)
{}

//----- ----- Setters ----- ----- //

void		MoveFollowComponent::setTagToFollow(const std::string & tagToFollow)
{
  this->_tagToFollow = tagToFollow;
}
