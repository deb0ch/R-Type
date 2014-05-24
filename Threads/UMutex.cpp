#ifdef __linux__

# include "UMutex.hh"

// Public

void	Mutex::lock()
{
  int	ret;

  if ((ret = pthread_mutex_lock(&_mutex)) != 0)
    throw MutexException(ret);
  _status = LOCKED;
}

bool	Mutex::trylock()
{
  int	ret;

  if ((ret = pthread_mutex_trylock(&_mutex)) != 0 && ret != EBUSY)
    throw MutexException(ret);
  _status = LOCKED;
  if (ret == EBUSY)
    return (false);
  return (true);
}

void	Mutex::unlock()
{
  int	ret;

  if ((ret = pthread_mutex_unlock(&_mutex)) != 0)
    throw MutexException(ret);
  _status = UNLOCKED;
}

IMutex::STATUS	Mutex::status() const
{
  return (_status);
}

Mutex::Mutex()
  : _status(UNLOCKED), _mutex(PTHREAD_MUTEX_INITIALIZER)
{}

Mutex::~Mutex()
{
  pthread_mutex_destroy(&_mutex);
}

// Private

#endif /* !__linux__ */
