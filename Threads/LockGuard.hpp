#ifndef LOCKGUARD_H_
# define LOCKGUARD_H_

# include <iostream>

template<typename T>
class LockGuard
{
public:
  LockGuard(T& mutex, bool already_owned = false) : _mutex(mutex), _is_locked(false)
  {
    if (!already_owned)
      this->_mutex.lock();
    this->_is_locked = true;
  }

  virtual	~LockGuard()
  {
    if (this->_is_locked)
      this->_mutex.unlock();
  }

  void		setUnLocked()
  {
    this->_is_locked = false;
  }

  LockGuard(const LockGuard &&lock) : _mutex(lock._mutex)
  {}

  LockGuard(const LockGuard&) = delete;
  LockGuard& operator=(const LockGuard&) = delete;

private:
  T&	_mutex;
  bool	_is_locked;
};

# define create_lock(mutex, ...) LockGuard<decltype(mutex)>(mutex, ## __VA_ARGS__)

#endif /* !LOCKGUARD_H_ */
