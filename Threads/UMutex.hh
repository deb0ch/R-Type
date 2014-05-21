#ifndef UMUTEX_H_
# define UMUTEX_H_

# include "MutexException.hh"
# include "IMutex.hh"

# include <pthread.h>

class UCondVar;

class Mutex : public IMutex
{
  friend class CondVar;
public:
  virtual void		lock();
  virtual bool		trylock();
  virtual void		unlock();
  virtual STATUS	status() const;

public:
			Mutex();
  virtual		~Mutex();

private:
			Mutex(const Mutex & other) = delete;
  Mutex &		operator=(const Mutex & other) = delete;

private:
  int			_ret;
  STATUS		_status;
  pthread_mutex_t	_mutex;
};

#endif /* !UMUTEX_H_ */
