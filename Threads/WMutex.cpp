#include "UMutex.hh"

// Public

void	UMutex::lock()
{
  if ((_ret = pthread_mutex_lock(&_mutex)) != 0)
    throw ThreadException(ThreadException::MUTEX, _ret, ThreadException::S_WARNING);
  _status = LOCKED;
}

void	UMutex::trylock()
{
  if ((_ret = pthread_mutex_trylock(&_mutex)) != 0 && _ret != EBUSY)
    throw ThreadException(ThreadException::MUTEX, _ret, ThreadException::S_WARNING);
  _status = LOCKED;
}

void	UMutex::unlock()
{
  if ((_ret = pthread_mutex_unlock(&_mutex)) != 0)
    throw ThreadException(ThreadException::MUTEX, _ret, ThreadException::S_ERROR);
  _status = UNLOCKED;
}

IMutex::STATUS	UMutex::status() const
{
  return (_status);
}

UMutex::UMutex()
  : _ret(0), _status(UNLOCKED), _mutex(PTHREAD_MUTEX_INITIALIZER)
{}

UMutex::~UMutex()
{
  pthread_mutex_destroy(&_mutex);
}

// Private
