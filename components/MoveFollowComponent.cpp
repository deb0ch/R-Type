#include	"MoveFollowComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveFollowComponent::MoveFollowComponent(Entity *target)
  : AComponent("MoveFollowComponent")
{
  this->_target = target;
}

MoveFollowComponent::MoveFollowComponent(const MoveFollowComponent &ref)
  : AComponent("MoveFollowComponent")
{
  this->_target = ref._target;
}

//----- ----- Destructor ----- ----- //
MoveFollowComponent::~MoveFollowComponent()
{}

//----- ----- Operators ----- ----- //
MoveFollowComponent	&MoveFollowComponent::operator=(const MoveFollowComponent &ref)
{
  this->_target = ref._target;
  return (*this);
}

//----- ----- Getters ----- ----- //
float	MoveFollowComponent::getX() const
{
  auto	pos = this->_target->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!pos)
    return (0);
  return (pos->getX());
}

float	MoveFollowComponent::getY() const
{
  auto	pos = this->_target->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!pos)
    return (0);
  return (pos->getY());
}

//----- ----- Setters ----- ----- //
