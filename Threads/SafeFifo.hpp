#ifndef		SAFEFIFO_H_
# define	SAFEFIFO_H_

#include <pthread.h>
#include <vector>
#include "Threads.hh"

template <typename T>
class SafeFifo
{
public:
  SafeFifo(){}
  virtual ~SafeFifo() {}

  void	push(const T &value) {
    ScopedMutex p(&(this->_mutex));

    this->fifo.push_back(value);
  }

  bool	tryPop(const T &value) {
    ScopedMutex p(&(this->_mutex));

    if (this->fifo.front() == value) {
      this->fifo.erase(this->fifo.begin());
      return (true);
    }
    return (false);
  }

  const T getNext(void) {	// TODO: const vraiment approprié ?
    ScopedMutex p(&(this->_mutex));

    if (this->fifo.empty())
      return (NULL);
    return ((this->fifo.front()));
  }

  const T getNextPop(void) {	// TODO: const vraiment approprié ?
    ScopedMutex p(&(this->_mutex));
    static T	res;

    if (this->fifo.empty())
      return (NULL);
    res = (this->fifo.front());
    this->fifo.erase(this->fifo.begin());
    return (res);
  }

  bool	isEmpty(void) {
    ScopedMutex p(&(this->_mutex));

    return (this->fifo.empty());
  }

  void	clear(void) {
    ScopedMutex p(&(this->_mutex));

    while (this->fifo.size())
      this->fifo.pop_back();
  }

  unsigned int getSize(void) {
    return (this->fifo.size());
  }

  bool	pop(void) {
    ScopedMutex p(&(this->_mutex));

    if (this->fifo.empty())
      return (false);
    this->fifo.erase(this->fifo.begin());
    return (true);
  }

protected:
  Mutex _mutex;
  std::vector<T> fifo;

private:
  SafeFifo(const SafeFifo& ref) = delete;
  SafeFifo& operator=(const SafeFifo& ref) = delete;

};

#endif /* !SAFEFIFO_H_ */
