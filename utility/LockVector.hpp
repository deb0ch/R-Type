#ifndef LOCKVECTOR_H_
# define LOCKVECTOR_H_

# include <vector>
# include "Mutex.hh"

template <typename T>
class LockVector : public std::vector<T>
{
public:
  typedef typename std::vector<T>::iterator iterator;
  typedef typename std::vector<T>::const_iterator const_iterator;

public:
  LockVector() : std::vector<T>()
  {}

  virtual	~LockVector()
  {}

  void		lock()
  {
    this->_mutex.lock();
  }

  void		unlock()
  {
    this->_mutex.unlock();
  }

  bool		trylock()
  {
    return this->_mutex.trylock();
  }

private:
  LockVector(const LockVector &) = delete;
  LockVector &operator=(const LockVector &) = delete;
protected:
  Mutex		_mutex;
};

#endif /* !LOCKVECTOR_H_ */
