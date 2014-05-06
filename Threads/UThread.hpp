#ifndef UTHREAD_H_
# define UTHREAD_H_

# include <pthread.h>
# include "IThread.hpp"
# include "Any.hpp"

template <typename T>
class Thread : public IThread<T>
{
public:
  virtual void	start(Any arg, T* obj, void (T::*fct)(Any &))
  {
    _container.obj = obj;
    _container.fct = fct;
    _container.arg = arg;
    if ((_ret = pthread_create(&_thread, NULL,
			       reinterpret_cast<void* (*)(void*)>(_threadEntry),
			       (void*)&_container))
	!= 0)
      throw ThreadException(ThreadException::THREAD, _ret, ThreadException::S_ERROR);
	_status = IThread<T>::RUNNING;
  }

  virtual void	exit()
  {
    pthread_exit(NULL);
    _status = IThread<T>::DEAD;
  }

  virtual void	wait()
  {
    if ((_ret = pthread_join(_thread, NULL)) != 0)
      throw ThreadException(ThreadException::THREAD, _ret, ThreadException::S_ERROR);
    _status = IThread<T>::DEAD;
  }

  virtual typename IThread<T>::STATUS	status() const
  {
    return (_status);
  }

public:
					Thread() { _status = IThread<T>::UNSTARTED; }
  virtual				~Thread() {}

private:
  					Thread(const Thread &) = delete;
  Thread &				operator=(const Thread &) = delete;

private:
  int					_ret;
  pthread_t				_thread;
  typename IThread<T>::STATUS		_status;

private:
  struct Container
  {
    T *obj;
    void (T::*fct)(Any &);
    Any arg;
  };
  struct Container				_container;
  static void*				_threadEntry(void* args)
  {
    Thread<T>::Container	*container = reinterpret_cast<Thread<T>::Container*>(args);

    (container->obj->*(container->fct))(container->arg);
	return (NULL);
  }
};

#endif /* !UTHREAD_H_ */
