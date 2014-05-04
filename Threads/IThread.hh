#ifndef ITHREAD_H_
# define ITHREAD_H_

# ifdef __linux__
#  include <pthread.h>
# endif /* !__linux__ */

# include <string>
# include "ThreadException.hh"
# include "../ECS/Any.hpp"

class	IThread
{
public:
  enum STATUS
    {
      UNSTARTED,
      RUNNING,
      DEAD
    };

public:
  virtual void		start(void* arg, void* (*fct)(void*)) = 0;
  virtual void		exit() = 0;
  virtual void		join() = 0;
  virtual STATUS	status() const = 0;

  virtual		 ~IThread() {}
};

#endif /* !ITHREAD_H_ */
