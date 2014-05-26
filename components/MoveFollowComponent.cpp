
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

unsigned int	MoveFollowComponent::getIdToFollow() const
{
  return this->_idToFollow;
}

void		MoveFollowComponent::setIdToFollow(unsigned int idToFollow)
{
  this->_idToFollow = idToFollow;
}

const std::string &	MoveFollowComponent::getTagToFollow() const
{
  return this->_tagToFollow;
}

void		MoveFollowComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_idToFollow;
  buffer << this->_tagToFollow;
}

void		MoveFollowComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_idToFollow;
  buffer >> this->_tagToFollow;
}

//----- ----- Setters ----- ----- //

void		MoveFollowComponent::setTagToFollow(const std::string & tagToFollow)
{
  this->_tagToFollow = tagToFollow;
}
