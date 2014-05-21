#include	"MoveFollowComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveFollowComponent::MoveFollowComponent(const unsigned long idToFollow)
  : AComponent("MoveFollowComponent")
{
  this->_idToFollow = idToFollow;
}

//----- ----- Destructor ----- ----- //
MoveFollowComponent::~MoveFollowComponent()
{}

unsigned long	MoveFollowComponent::getIdToFollow() const {
  return this->_idToFollow;
}
void		MoveFollowComponent::setIdToFollow(const unsigned long idToFollow) {
    this->_idToFollow = idToFollow;
}
