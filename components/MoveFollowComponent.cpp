#include	"MoveFollowComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveFollowComponent::MoveFollowComponent(const unsigned long idToFollow)
  : AComponent("MoveFollowComponent")
{
  this->_idToFollow = idToFollow;
}

MoveFollowComponent::MoveFollowComponent(const MoveFollowComponent &ref)
  : AComponent("MoveFollowComponent")
{
  this->_idToFollow = ref._idToFollow;
}

//----- ----- Destructor ----- ----- //
MoveFollowComponent::~MoveFollowComponent()
{}

//----- ----- Operators ----- ----- //
MoveFollowComponent	&MoveFollowComponent::operator=(const MoveFollowComponent &ref)
{
  this->_idToFollow = ref._idToFollow;
  return (*this);
}

unsigned long	MoveFollowComponent::getIdToFollow() const {
  return this->_idToFollow;
}
void		MoveFollowComponent::setIdToFollow(const unsigned long idToFollow) {
    this->_idToFollow = idToFollow;
}
