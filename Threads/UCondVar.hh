#ifndef CONDVAR_H_
# define CONDVAR_H_

#include <pthread.h>
#include "ICondVar.hh"

class CondVar : public ICondVar
{
private:
  CondVar& operator=(const CondVar&) = delete;
  CondVar(const CondVar &) = delete;

protected:
  pthread_cond_t	cond;
  //  Mutex			mutex;

public:
  CondVar();
  virtual ~CondVar();

  virtual void wait(Mutex *mutex);
  virtual void signal(void);
  virtual void broadcast(void);
};

#endif /* !CONDVAR_H_ */
