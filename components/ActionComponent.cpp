#include	<algorithm>
#include	"ActionComponent.hh"

ActionComponent::ActionComponent()
  : ACopyableComponent("ActionComponent")
{}

ActionComponent::~ActionComponent()
{}

bool		ActionComponent::hasChanged(const std::string &action) const
{
  auto it = this->_actions_changed.find(action);
  if (it != this->_actions_changed.end())
    return (this->_actions_changed.at(action));
  return (false);
}

void		ActionComponent::resetChange(const std::string &action)
{
  auto it = this->_actions_changed.find(action);
  if (it != this->_actions_changed.end())
    this->_actions_changed[action] = false;
}

bool		ActionComponent::isActive(const std::string &action) const
{
  auto it = this->_actions.find(action);
  if (it != this->_actions.end())
    return (it->second);
  return (false);
}

ActionComponent	*ActionComponent::addAction(const std::string &action)
{
  auto it = this->_actions.find(action);
  if (it == this->_actions.end())
    {
      this->_actions_changed[action] = false;
      this->_actions[action] = false;
    }
  return (this);
}

void		ActionComponent::setAction(const std::string &action, const bool status)
{
  auto it = this->_actions.find(action);
  if (it != this->_actions.end())
    {
      if (this->_actions[action] != status)
	this->_actions_changed[action] = true;
      this->_actions[action] = status;
    }
}

void			ActionComponent::resetActions()
{
  std::for_each(this->_actions.begin(), this->_actions.end(),
		[] (std::pair<const std::string, bool> &pair)
		{
		  pair.second = false;
		});
}

void			ActionComponent::serialize(IBuffer &buffer) const
{
  unsigned int		nb;

  nb = this->_actions.size();
  buffer << nb;
  std::for_each(this->_actions.begin(), this->_actions.end(),
		[this, &buffer] (const std::pair<std::string, bool> &pair)
		{
		  buffer << pair.first;
		});
}

void			ActionComponent::unserialize(IBuffer &buffer)
{
  unsigned int		nb;
  std::string		action_name;

  buffer >> nb;
  for(unsigned int i = 0; i < nb; ++i)
    {
      buffer >> action_name;
      this->addAction(action_name);
    }
}

void	ActionComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("actions=.+")))
    this->_actions[lastline.substr(8)] = false;
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void		ActionComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  std::for_each(this->_actions.begin(), this->_actions.end(), [&output, indent](const std::pair<std::string, bool>& pair)
		{
		  output << std::string(indent, '\t') << "actions=" << pair.first << std::endl;
		});
}
