#include	"MoveFollowComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveFollowComponent::MoveFollowComponent(Entity *entity)
  : AComponent("MoveFollowComponent")
{
  this->_entity = entity;
}

MoveFollowComponent::MoveFollowComponent(const MoveFollowComponent &ref)
  : AComponent("MoveFollowComponent")
{
  this->_entity = ref._entity;
}

//----- ----- Destructor ----- ----- //
MoveFollowComponent::~MoveFollowComponent()
{}

//----- ----- Operators ----- ----- //
MoveFollowComponent	&MoveFollowComponent::operator=(const MoveFollowComponent &ref)
{
  this->_entity = ref._entity;
  return (*this);
}

/*
unsigned long	MoveFollowComponent::getIdToFollow() const {
  return this->_idToFollow;
}
void		MoveFollowComponent::setIdToFollow(const unsigned long idToFollow) {
    this->_idToFollow = idToFollow;
}
*/

float		MoveFollowComponent::getX() const {
  auto pos = this->_entity->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!pos)
    return 0;
  return pos->getX();
}

float		MoveFollowComponent::getY() const {
  auto pos = this->_entity->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!pos)
    return 0;
  return pos->getY();
}
