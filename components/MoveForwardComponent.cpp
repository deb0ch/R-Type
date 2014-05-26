#include "MoveForwardComponent.hh"
#include "Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
MoveForwardComponent::MoveForwardComponent(MoveForwardComponent::Direction dir)
: ACopyableComponent("MoveForwardComponent")
{
	this->_direction = dir;
	if (dir == MoveForwardComponent::UP)
		this->_actions.push_back("UP");
	else if (dir == MoveForwardComponent::DOWN)
		this->_actions.push_back("DOWN");
	else if (dir == MoveForwardComponent::RIGHT)
		this->_actions.push_back("RIGHT");
	else if (dir == MoveForwardComponent::LEFT)
		this->_actions.push_back("LEFT");
}


MoveForwardComponent::MoveForwardComponent(MoveForwardComponent::Direction dir,
	const Direction seconddir)
	: ACopyableComponent("MoveForwardComponent")
{
	this->_direction = dir;
	if (dir == MoveForwardComponent::UP || seconddir == MoveForwardComponent::UP)
		this->_actions.push_back("UP");
	if (dir == MoveForwardComponent::DOWN || seconddir == MoveForwardComponent::DOWN)
		this->_actions.push_back("DOWN");
	if (dir == MoveForwardComponent::RIGHT || seconddir == MoveForwardComponent::RIGHT)
		this->_actions.push_back("RIGHT");
	if (dir == MoveForwardComponent::LEFT || seconddir == MoveForwardComponent::LEFT)
		this->_actions.push_back("LEFT");
}

//----- ----- Destructor ----- ----- //
MoveForwardComponent::~MoveForwardComponent()
{}

//----- ----- Methods ----- ----- //

const std::vector<std::string> & MoveForwardComponent::getDirection() const
{
	return (this->_actions);
}

void MoveForwardComponent::setDirection(const MoveForwardComponent::Direction dir)
{
	this->_direction = dir;
}

void	MoveForwardComponent::serialize(IBuffer &) const
{}

void	MoveForwardComponent::unserialize(IBuffer &)
{}
