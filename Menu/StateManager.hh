#ifndef STATEMANAGER_H_
# define STATEMANAGER_H_

#include	<vector>
#include	"IState.hh"
#include	"Timer.hh"

class		StateManager
{
public:
	StateManager();
	virtual ~StateManager();
	void	popState();
	void	pushState(IState* state);
	void	update();
	void	render(const Timer&);

protected:
	std::vector<IState *>	_states;
};

#endif /* !STATEMANAGER_H_ */