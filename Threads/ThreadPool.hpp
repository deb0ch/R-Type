#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <vector>
# include "IThread.hpp"
# include "ScopedMutex.hh"
# include "Mutex.hh"
# include "CondVar.hh"
# include "SafeFifo.hpp"
# include "Task.hpp"

// TODO: ajouter methode wait();

extern "C"
{
  void *	threadEntryPoint(void * threadPoolPtr);
}

class ThreadPool
{
  // Public
public :
  enum	eStatus
    {
      RUNNING,
      STOPPED
    };

  void			addTask(ITask * task)
  {
    this->_tasks.push(task);
    _condvar.signal();
    _condvar2.wait(&_mutex);
  }

  eStatus		getStatus() const
  {
    return (_status);
  }

  // Coplien

  ThreadPool(unsigned int nbThread)
    : _nbThread(nbThread), _status(RUNNING)
  {
    for (unsigned int i = 0; i < nbThread; i++)
      {
	this->_pool.push_back(new Thread< ThreadPool >());
	this->_pool[i]->start(&threadEntryPoint, static_cast<void *>(this));
	// this->_pool[i]->start(this, &ThreadPool::runThread, Any());
      }
  }

  ~ThreadPool()
  {
    _mutex.lock();
    _status = STOPPED;
    _mutex.unlock();
    _condvar.broadcast();
    for (auto it = _pool.begin(); it != _pool.end(); ++it)
      {
	(*it)->wait();
	delete *it;
	_condvar.broadcast();
      }
  }

  void*	runThread()
  {
    ITask *	task;

    _condvar2.signal();
    if (_status == STOPPED)
      {
	std::cout << "Catastrophe2 !!!" << std::endl;
      }
    while (42)
      {
	while (_tasks.isEmpty() && _status == RUNNING)
	  _condvar.wait(&_mutex);
	if (_status == STOPPED)
	  return (NULL);
	if ((task = this->_tasks.getNextPop()) != NULL)
	  {
	    (*task)();
	    delete task;
	  }
      }
    return (NULL);
  }

  // Private

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

private:
  const unsigned int			_nbThread;
  volatile eStatus			_status;
  CondVar				_condvar;
  CondVar				_condvar2;
  Mutex					_mutex;
  SafeFifo<ITask *>			_tasks;
  std::vector<Thread< ThreadPool > *>	_pool;
};

extern "C"
{
  void *	threadEntryPoint(void * threadPoolPtr)
  {
    static_cast<ThreadPool *>(threadPoolPtr)->runThread();
    return (NULL);
  }
}

#endif /* !THREADPOOL_H_ */
