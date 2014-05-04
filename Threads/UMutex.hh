#ifndef UMUTEX_H_
# define UMUTEX_H_

# include "ThreadException.hh"
# include "IMutex.hh"

# ifdef __linux__
#  include <pthread.h>
# endif /* !__linux__ */

class UMutex : public IMutex
{
public:
  virtual void		lock();
  virtual void		trylock();
  virtual void		unlock();
  virtual STATUS	status() const;

public:
			UMutex();
  virtual		~UMutex();

private:
			UMutex(const UMutex & other) = delete;
  UMutex &		operator=(const UMutex & other) = delete;

private:
  int			_ret;
  STATUS		_status;
  pthread_mutex_t	_mutex;
};

#endif /* !UMUTEX_H_ */
