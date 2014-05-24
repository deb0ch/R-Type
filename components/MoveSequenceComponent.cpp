#include	"MoveSequenceComponent.hh"

MoveSequenceComponent::MoveSequenceComponent(const MoveSequenceComponent::Sens sens,
					     const unsigned int tickToChange)
  : ACopyableComponent("MoveSequenceComponent")
{
  this->_sens = sens;
  this->_tick = 0;
  this->_tickToChange = tickToChange;
  this->_index = 0;
  if (sens == MoveSequenceComponent::UP_DOWN)
    this->_actions = { "UP", "DOWN" };
  else if (sens == MoveSequenceComponent::RIGHT_LEFT)
    this->_actions = { "RIGHT", "LEFT" };
}

//----- ----- Destructor ----- ----- //
MoveSequenceComponent::~MoveSequenceComponent()
{}

//----- ----- Operators ----- ----- //
//----- ----- Methods ----- ----- //

void  MoveSequenceComponent::incrementTick()
{
  ++this->_tick;
  if (this->_tick == this->_tickToChange)
    {
      this->_tick = 0;
      ++this->_index;
      if (this->_index >= this->_actions.size())
	this->_index = 0;
    }
}

const std::string & MoveSequenceComponent::getAction() const
{
  return (this->_actions[this->_index]);
}

void		MoveSequenceComponent::serialize(IBuffer &) const
{}

void		MoveSequenceComponent::unserialize(IBuffer &)
{}
