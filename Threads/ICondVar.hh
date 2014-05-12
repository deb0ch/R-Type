#ifndef ICONDVAR_H_
# define ICONDVAR_H_

# include "Mutex.hh"

class Mutex;

class ICondVar
{
public:
  virtual void wait(Mutex *) = 0;
  virtual void signal(void) = 0;
  virtual void broadcast(void) = 0;

  virtual      ~ICondVar() {}
};

#endif /* !ICONDVAR_H_ */
