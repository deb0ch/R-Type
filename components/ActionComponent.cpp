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
    return (it->second);
  return (false);
}

void		ActionComponent::resetChange(const std::string &action)
{
  auto it = this->_actions_changed.find(action);
  if (it != this->_actions_changed.end())
    it->second = false;
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
