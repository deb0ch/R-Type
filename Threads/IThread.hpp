#ifndef ITHREAD_H_
# define ITHREAD_H_

# ifdef __linux__
#  include <pthread.h>
# endif /* !__linux__ */

# include <string>
# include "ThreadException.hh"
# include "Any.hpp"

template <typename T>
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
  virtual void		start(T* obj, void* (T::*fct)(Any), Any arg) = 0;
  virtual void		start(void* (*fct)(void*), void* arg) = 0;
  virtual void		exit() = 0;
  virtual void		wait() = 0;
  virtual STATUS	status() const = 0;

  virtual		~IThread() {}
};

#endif /* !ITHREAD_H_ */
