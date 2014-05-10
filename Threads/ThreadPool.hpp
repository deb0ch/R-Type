#ifndef THREADPOOL_H_
# define THREADPOOL_H_

# include <vector>
# include "IThread.hpp"
# include "Mutex.hh"
# include "CondVar.hh"
# include "SafeFifo.hpp"

template <typename T>
class ThreadPool
{
  // Public
public :
  void			addTask(Any arg, T* obj, void (T::*fct)(Any &))
  {
    TaskContainer*	container = new TaskContainer();

    container->arg = arg;
    container->obj = obj;
    container->fct = fct;
    this->_task.push(container);
    _condvar.signal();
  }

  // Coplien

  ThreadPool(unsigned int nbThread)
  {
    Thread<T> *thread;

    this->_status = RUNNING;
    this->_nbThread = nbThread;
    for (unsigned int i = 0; i < nbThread; i++)
      {
	this->_pool.push_back(new Thread<T>());
	this->_pool[i]->start(Any(), this, runThread);
      }
  }

  ~ThreadPool()
  {
    _mutex.lock();		// Is this really necessary ?
    _status = STOPPED;
    _mutex.unlock();		// Is this really necessary ?
    _condvar.broadcast();
    for (auto it = _pool.begin(); it != _pool.end(); ++it)
      {
	(*it)->wait();		// Is this really necessary ?
	delete *it;
      }
  }

  // Private

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

private :
  void	runThread(Any)
  {
    TaskContainer *toto;

    while (42)
      {
	while (_task.isEmpty() && _status == RUNNING)
	  _condvar.wait(&_mutex);
	if (_status == STOPPED)
	  return ;
	if ((toto = this->_task.getNext()) != NULL)
	  {
	    (toto->obj->*(toto->fct))(toto->arg);
	    delete toto;
	  }
      }
  }

private:
  struct TaskContainer
  {
    T *obj;
    void (T::*fct)(Any &);
    Any arg;
  };

  enum	e_status
    {
      RUNNING,
      STOPPED
    };

  CondVar			_condvar;
  Mutex				_mutex;
  e_status			_status;
  SafeFifo<TaskContainer *>     _task;
  std::vector<Thread<T> *>	_pool;
  unsigned int			_nbThread;
};

#endif /* !THREADPOOL_H_ */
