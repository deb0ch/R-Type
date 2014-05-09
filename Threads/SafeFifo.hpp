#ifndef		SAFEQUEUE_H_
# define	SAFEQUEUE_H_

#include <pthread.h>
#include <vector>
#include "Mutex.hh"
#include "ScopedMutex.hh"
#include "ISafeQueue.hh"
#include "CondVar.hh"
#include "Exception.hh"

template <typename T>
class SafeFifo : public ISafeQueue<T>
{
protected:
  Mutex mutex;
  CondVar cond;
  std::vector<T> fifo;

public:
  SafeFifo()
  {
  }

  SafeFifo(const SafeFifo& ref)
  {
    this->mutex = ref.mutex;
    this->cond = ref.cond;
  }

  ~SafeFifo()
  {
  }

  SafeFifo&	operator=(const SafeFifo& ref)
  {
    this->mutex = ref.mutex;
    return (*this);
  }

  const Mutex &getMutex() const
  {
    return (this->mutex);
  }

  void	setMutex(const Mutex &mutex)
  {
    this->mutex = mutex;
  }

  void	push(const T &value)
  {
    ScopedMutex p(&(this->mutex));

    this->fifo.push_back(value);
    this->cond.signal();
  }

  bool	tryPop(const T &value)
  {
    ScopedMutex p(&(this->mutex));

    if (this->fifo.front() == value)
      {
	this->fifo.erase(this->fifo.begin());
	return (true);
      }
    return (false);
  }

  const T &getNext(void)
  {
    ScopedMutex p(&(this->mutex));

    if (this->fifo.empty())
      throw Exception("error, empty fifo");
    return ((this->fifo.front()));
  }

  const T &getNextPop(void)
  {
    ScopedMutex p(&(this->mutex));

    static T	res;

    if (this->fifo.empty())
      throw Exception("error, empty fifo");
    res = (this->fifo.front());
    this->fifo.erase(this->fifo.begin());
    return (res);
  }

  bool	isFinished(void)
  {
    ScopedMutex p(&(this->mutex));

    return (this->fifo.empty());
  }

  void	setFinished(void)
  {
    ScopedMutex p(&(this->mutex));

    while (this->fifo.size())
      this->fifo.pop_back();
  }

  unsigned int getSize(void)
  {
    return (this->fifo.size());
  }

  int	pop(void)
  {
    ScopedMutex p(&(this->mutex));

    while (this->fifo.empty())
      this->cond.wait(&(this->mutex));
    this->fifo.erase(this->fifo.begin());
    return (0);
  }
};

#endif /* !SAFEQUEUE_H_ */