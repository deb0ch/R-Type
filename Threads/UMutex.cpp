#ifdef __linux__

# include "UMutex.hh"

// Public

void	Mutex::lock()
{
  if ((_ret = pthread_mutex_lock(&_mutex)) != 0)
    throw MutexException(_ret);
  _status = LOCKED;
}

void	Mutex::trylock()
{
  if ((_ret = pthread_mutex_trylock(&_mutex)) != 0 && _ret != EBUSY)
    throw MutexException(_ret);
  _status = LOCKED;
}

void	Mutex::unlock()
{
  if ((_ret = pthread_mutex_unlock(&_mutex)) != 0)
    throw MutexException(_ret);
  _status = UNLOCKED;
}

IMutex::STATUS	Mutex::status() const
{
  return (_status);
}

Mutex::Mutex()
  : _ret(0), _status(UNLOCKED), _mutex(PTHREAD_MUTEX_INITIALIZER)
{}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&_mutex);
}

// Private

#endif /* !__linux__ */
