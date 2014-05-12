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
    _condvar.broadcast();
  }

  // Coplien

  ThreadPool(unsigned int nbThread)
  {
    int a;
    this->_nbThread = nbThread;
    for (unsigned int i = 0; i < nbThread; i++)
      {
	this->_pool.push_back(new Thread< ThreadPool<T> >());
	this->_pool[i]->start(&a, this, &ThreadPool<T>::runThread);
      }
  }

  ~ThreadPool()
  {
    for (auto it = _pool.begin(); it != _pool.end(); ++it)
      {
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
	if (_task.isEmpty())
	  _condvar.wait(&_mutex);
	try {
	  task = this->_task.getNextPop();
	  (task->obj->*(task->fct))(task->arg);
	  delete task;
	} catch (std::exception e) {}
      }
  }

private:
  struct TaskContainer
  {
    T *obj;
    void (T::*fct)(Any &);
    Any arg;
  };

  CondVar				_condvar;
  Mutex					_mutex;
  SafeFifo<TaskContainer*>		_task;
  std::vector<Thread< ThreadPool<T> >*>	_pool;
  unsigned int				_nbThread;
};

#endif /* !THREADPOOL_H_ */
