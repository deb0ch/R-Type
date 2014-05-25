#ifndef		SAFEFIFO_H_
# define	SAFEFIFO_H_

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

  unsigned int	size() {
    ScopedMutex p(&(this->_mutex));
    return this->fifo.size();
  }

  bool	tryPop(const T &value) {
    ScopedMutex p(&(this->_mutex));

    if (this->fifo.front() == value) {
      this->fifo.erase(this->fifo.begin());
      return (true);
    }
    return (false);
  }

  T &getNext(void) {
    ScopedMutex p(&(this->_mutex));

    if (this->fifo.empty())
      throw std::exception();
    return ((this->fifo.front()));
  }

  T &getNextPop(void) {
    ScopedMutex p(&(this->_mutex));
    static T	res;

    if (this->fifo.empty())
      throw std::exception();
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
