
#include "StateManager.hh"

StateManager::StateManager()
{
  this->_running = true;
}

StateManager::~StateManager()
{}

void	StateManager::popState()
{
	if (this->_states.size() > 0)
		this->_states.pop_back();
}

void	StateManager::pushState(IState* state)
{
	this->_states.push_back(state);
}

void	StateManager::update()
{
	if (this->_states.size() > 0)
		this->_states.back()->update(*this);
}

void	StateManager::render(const Timer &timer)
{
	if (this->_states.size() > 0)
		this->_states.back()->render(timer);
}

void	StateManager::exit()
{
  this->_running = false;
}

bool	StateManager::isRunning() const
{
  return this->_running;
}
