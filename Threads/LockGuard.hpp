#ifndef LOCKGUARD_H_
# define LOCKGUARD_H_

# include <iostream>

template<typename T>
class LockGuard
{
public:
  LockGuard(T& mutex, bool already_owned = false) : _mutex(mutex)
  {
    if (!already_owned)
      this->_mutex.lock();
    std::cout << "LOCK" << std::endl;
  }

  virtual ~LockGuard()
  {
    this->_mutex.unlock();
    std::cout << "UNLOCK" << std::endl;
  }

  LockGuard(const LockGuard &&lock) : _mutex(lock._mutex)
  {}

  LockGuard(const LockGuard&) = delete;
  LockGuard& operator=(const LockGuard&) = delete;

private:
  T&  _mutex;
};

# define create_lock(mutex, ...) LockGuard<decltype(mutex)>(mutex, __VA_ARGS__);

#endif /* !LOCKGUARD_H_ */
