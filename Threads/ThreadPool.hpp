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
    _status = STOPPED;
    //_condvar.broadcast();
    for (auto it = _pool.begin(); it != _pool.end(); ++it) {
      //_condvar.broadcast();
      //(*it)->wait();
      delete *it;
      //_condvar.broadcast();
    }
  }

  void			addTask(ITask * task) {
    this->_tasks.push(task);
    _condvar.broadcast();
  }

  eStatus		getStatus() const {
    return (_status);
  }

  void			runThread(Any) {
    ITask*		task;

    while (/*_status == RUNNING*/ 1) {
      if (_tasks.isEmpty())
	_condvar.wait(&_mutex);
      //if (_status == RUNNING) {
	try {
	  task = this->_tasks.getNextPop();
	  (*task)();
	  delete task;
	} catch (std::exception) { }
	//}
    }
  }

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

private:
  const unsigned int			_nbThread;
  volatile eStatus			_status;
  CondVar				_condvar;
  Mutex					_mutex;
  SafeFifo<ITask *>			_tasks;
  std::vector<Thread< ThreadPool > *>	_pool;

};

#endif /* !THREADPOOL_H_ */
