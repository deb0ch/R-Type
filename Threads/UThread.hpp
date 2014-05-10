#ifndef UTHREAD_H_
# define UTHREAD_H_

# include <pthread.h>
# include "IThread.hpp"
# include "Any.hpp"

template <typename T>
class Thread : public IThread<T>
{
public:
  virtual void				start(Any arg, T* obj, void (T::*fct)(Any &))
  {
    _container.obj = obj;
    _container.fct = fct;
    _container.arg = arg;
    if ((_ret = pthread_create(&this->_thread, NULL,
			       reinterpret_cast<void* (*)(void*)>(this->_threadEntry),
			       (void*)&this->_container))
	!= 0)
      throw ThreadException(_ret);
    this->_status = IThread<T>::RUNNING;
  }

  virtual void	exit()
  {
    pthread_exit(NULL);
    this->_status = IThread<T>::DEAD;
  }

  virtual void				wait()
  {
    if ((this->_ret = pthread_join(this->_thread, NULL)) != 0)
      throw ThreadException(_ret);
    this->_status = IThread<T>::DEAD;
  }

  virtual typename IThread<T>::STATUS	status() const
  {
    return (this->_status);
  }

public:
  Thread() { this->_status = IThread<T>::UNSTARTED; }
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

  struct Container			_container;

  static void*				_threadEntry(void* args)
  {
    Thread<T>::Container	*container = reinterpret_cast<Thread<T>::Container*>(args);

    (container->obj->*(container->fct))(container->arg);
    return (NULL);
  }
};

#endif /* !UTHREAD_H_ */
