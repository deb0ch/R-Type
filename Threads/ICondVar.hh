#ifndef		ICONDVAR_H_
# define	ICONDVAR_H_

#include "Threads.hh"

class ICondVar
{
public:
  virtual ~ICondVar() {}
  virtual void wait(Mutex *) = 0;
  virtual void signal(void) = 0;
  virtual void broadcast(void) = 0;
};

#endif /* !ICONDVAR_H_ */