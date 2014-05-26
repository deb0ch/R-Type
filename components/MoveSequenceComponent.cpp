#include	"MoveSequenceComponent.hh"

MoveSequenceComponent::MoveSequenceComponent(const std::vector<std::string> &actions,
					     const unsigned int tickToChange)
  : ACopyableComponent("MoveSequenceComponent")
{
  this->_tick = 0;
  this->_tickToChange = tickToChange;
  this->_index = 0;
  this->_actions = actions;
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

const std::string &MoveSequenceComponent::getAction() const
{
  static std::string	empty("");
  if (this->_actions.size() == 0)
    return (empty);
  return (this->_actions[this->_index]);
}

void		MoveSequenceComponent::serialize(IBuffer &) const
{}

void		MoveSequenceComponent::unserialize(IBuffer &)
{}
