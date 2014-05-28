#ifndef ISTATE_H_
# define ISTATE_H_

class		StateManager;

class		IState
{
private:
  IState(const IState&);
  IState&	operator=(const IState&);

public:
  IState();
  virtual	~IState();

  virtual bool	isTransparent() const = 0;
};

#endif /* !ISTATE_H_ */