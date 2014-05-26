#ifndef UCONDVAR_H_
# define UCONDVAR_H_

#include <pthread.h>
#include "ICondVar.hh"

class CondVar : public ICondVar
{
private:
  CondVar& operator=(const CondVar&) = delete;
  CondVar(const CondVar &) = delete;

protected:
  pthread_cond_t	cond;

public:
  CondVar();
  virtual ~CondVar();

  virtual void wait(Mutex *mutex);
  virtual void signal(void);
  virtual void broadcast(void);
};

#endif /* !UCONDVAR_H_ */
