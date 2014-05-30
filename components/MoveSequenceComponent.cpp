#include	"MoveSequenceComponent.hh"

MoveSequenceComponent::MoveSequenceComponent(const std::vector<std::string> &actions,
					     float tickToChange)
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

void  MoveSequenceComponent::incrementTick(float delta)
{
  this->_tick += delta;
  if (this->_tick >= this->_tickToChange)
    {
      this->_tick -= this->_tickToChange;
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

void		MoveSequenceComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_tick;
  buffer << this->_tickToChange;
  buffer << this->_index;
  buffer << static_cast<unsigned int>(this->_actions.size());
  std::for_each(this->_actions.begin(), this->_actions.end(),
		[&buffer] (const std::string &action)
		{
		  buffer << action;
		});
}

void		MoveSequenceComponent::unserialize(IBuffer &buffer)
{
  unsigned int	nb;

  buffer >> this->_tick;
  buffer >> this->_tickToChange;
  buffer >> this->_index;
  buffer >> nb;
  this->_actions.clear();
  for(unsigned int i = 0; i < nb; ++i)
    {
      std::string str;

      buffer >> str;
      this->_actions.push_back(str);
    }
}

void	MoveSequenceComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("action=.+")))
    this->_actions.push_back(lastline.substr(7));
  else if (std::regex_match(lastline, std::regex("tickToChange=.+")))
    this->_tickToChange = std::stof(lastline.substr(13));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	MoveSequenceComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  std::for_each(this->_actions.begin(), this->_actions.end(),[&output, indent](const std::string &action)
		{
		  output << std::string(indent, '\t') << "action=" << action << std::endl;
		});
  output << std::string(indent, '\t') << "tickToChange=" << this->_tickToChange << std::endl;
}
