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
    TaskContainer*	task = new TaskContainer();

    task->arg = arg;
    task->obj = obj;
    task->fct = fct;
    this->_task.push(task);
    _condvar.signal();
  }

  // Coplien

  ThreadPool(unsigned int nbThread)
  {
    this->_status = RUNNING;
    this->_nbThread = nbThread;
    for (unsigned int i = 0; i < nbThread; i++)
      {
	this->_pool.push_back(new Thread< ThreadPool<T> >());
	this->_pool[i]->start(Any(), this, &ThreadPool<T>::runThread);
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
      }
  }

  // Private

private :
  ThreadPool() = delete;
  ThreadPool(const ThreadPool& other) = delete;
  ThreadPool &operator=(const ThreadPool & other) = delete;

private :
  void	runThread(Any &)
  {
    TaskContainer *task;

    while (42)
      {
	while (_task.isEmpty() && _status == RUNNING)
	  _condvar.wait(&_mutex);
	if (_status == STOPPED)
	  return ;
	if ((task = this->_task.getNext()) != NULL)
	  {
	    (task->obj->*(task->fct))(task->arg);
	    delete task;
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

  CondVar				_condvar;
  Mutex					_mutex;
  e_status				_status;
  SafeFifo<TaskContainer*>		_task;
  std::vector<Thread< ThreadPool<T> >*>	_pool;
  unsigned int				_nbThread;
};

#endif /* !THREADPOOL_H_ */
