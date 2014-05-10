
#include "ScopedMutex.hh"

ScopedMutex::ScopedMutex(IMutex *mutex)
{
  this->_mutex = mutex;
  this->_mutex->lock();
}

ScopedMutex::~ScopedMutex()
{
  this->_mutex->unlock();
}
