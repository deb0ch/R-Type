#ifndef CONDVAR_H_
# define CONDVAR_H_

#include <pthread.h>
#include "ICondVar.hh"

class CondVar : public ICondVar
{
protected:
  pthread_cond_t	cond;
  Mutex			mutex;

public:
  CondVar();
  CondVar(const CondVar&);
  ~CondVar();
  CondVar&	operator=(const CondVar&);

  pthread_cond_t	getCond() const;
  void	setCond(pthread_cond_t);

  void wait(Mutex *mutex);
  void signal(void);
  void broadcast(void);
};

#endif /* !CONDVAR_H_ */
