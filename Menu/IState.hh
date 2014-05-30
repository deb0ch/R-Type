#ifndef ISTATE_H_
# define ISTATE_H_

class		Timer;
class		StateManager;

class		IState
{
private:
	IState(const IState&);
	IState&	operator=(const IState&);

public:
	IState() {};
	virtual	~IState() {};

	virtual void update(StateManager&) = 0;
	virtual void render(const Timer&) = 0;
};

#endif /* !ISTATE_H_ */