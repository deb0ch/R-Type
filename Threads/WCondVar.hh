#ifndef WCONDVAR_H_
# define WCONDVAR_H_

#include "ICondVar.hh"

class CondVar : public ICondVar
{
protected:
	PCONDITION_VARIABLE cond;
	Mutex			mutex;

public:
	CondVar();
	CondVar(const CondVar&);
	~CondVar();
	CondVar&	operator=(const CondVar&);

	void wait(Mutex *mutex);
	void signal(void);
	void broadcast(void);
};

#endif /* !WCONDVAR_H_ */
