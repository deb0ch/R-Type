#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <vector>
# include "IThread.hpp"
# include "ScopedMutex.hh"
# include "Mutex.hh"
# include "CondVar.hh"
# include "SafeFifo.hpp"
# include "Task.hpp"

class ThreadPool
{
public :
  enum	eStatus
    {
      RUNNING,
      STOPPED
    };

public:
  ThreadPool(unsigned int nbThread) : _nbThread(nbThread), _status(RUNNING) {
    for (unsigned int i = 0; i < nbThread; i++) {
      this->_pool.push_back(new Thread< ThreadPool >());
      this->_pool[i]->start(this, &ThreadPool::runThread, Any());
    }
  }

  ~ThreadPool() {
    while (!_tasks.isEmpty());
    _status = STOPPED;
    _condvar.broadcast();
    for (auto it = _pool.begin(); it != _pool.end(); ++it) {
      (*it)->wait();
      delete *it;
    }
  }

  void			addTask(ITask * task) {
    this->_tasks.push(task);
    _condvar.broadcast();
  }

  void			runThread(Any) {
    ITask*		task;

    while (_status == RUNNING) {
      if (_tasks.isEmpty()) {
	this->_mutex.lock();
	_condvar.wait(&_mutex);
	this->_mutex.unlock();
      }
      if (_status == RUNNING) {
	try {
	  task = this->_tasks.getNextPop();
	  (*task)();
	} catch (std::exception) {}
      }
    }
  }

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

private:
  const unsigned int			_nbThread;
  eStatus				_status;
  CondVar				_condvar;
  Mutex					_mutex;
  SafeFifo<ITask *>			_tasks;
  std::vector<Thread< ThreadPool > *>	_pool;

};

#endif /* !THREADPOOL_H_ */
