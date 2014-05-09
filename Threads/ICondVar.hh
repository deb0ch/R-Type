#ifndef		ICONDVAR_H_
# define	ICONDVAR_H_

#ifdef __linux__
#include "UMutex.hh"
#elif _WIN32
#include "WMutex.hh"
#endif

class Mutex;

class ICondVar
{
public:
  virtual ~ICondVar() {}
  virtual void wait(Mutex *) = 0;
  virtual void signal(void) = 0;
  virtual void broadcast(void) = 0;
};

#endif /* !ICONDVAR_H_ */
