#include "ActionComponent.hh"

ActionComponent::ActionComponent()
  : AComponent("ActionComponent")
{}

ActionComponent::~ActionComponent()
{}

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
    this->_actions[action] = false;
  return (this);
}

void		ActionComponent::setAction(const std::string &action, const bool status)
{
  auto it = this->_actions.find(action);
  if (it != this->_actions.end())
    this->_actions[action] = status;
}
