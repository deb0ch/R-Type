#ifndef UTHREAD_H_
# define UTHREAD_H_

# include <pthread.h>

# include "IThread.hpp"
# include "Any.hpp"

template <typename T>
class Thread : public IThread<T>
{
public:
  virtual void				start(T* obj, void (T::*fct)(Any), Any arg)
  {
    _containerArg.obj = obj;
    _containerArg.fct = fct;
    _containerArg.arg = arg;
    if ((_ret = pthread_create(&(this->_thread),
			       NULL,
			       static_cast<void* (*)(void*)>(this->_threadEntryArg),
			       static_cast<void*>(&this->_containerArg)))
	!= 0)
      throw ThreadException(_ret);
    this->_status = IThread<T>::RUNNING;
  }

  virtual void				start(T* obj, void (T::*fct)())
  {
    _container.obj = obj;
    _container.fct = fct;
    if ((_ret = pthread_create(&(this->_thread),
			       NULL,
			       static_cast<void* (*)(void*)>(this->_threadEntry),
			       static_cast<void*>(&this->_container)))
	!= 0)
      throw ThreadException(_ret);
    this->_status = IThread<T>::RUNNING;
  }

  virtual void				start(void* (*fct)(void*), void* arg)
  {
    if ((_ret = pthread_create(&(this->_thread), NULL, fct, arg)) != 0)
      throw ThreadException(_ret);
    this->_status = IThread<T>::RUNNING;
  }

  virtual void				exit()
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
  struct	Container
  {
    T *		obj;
    void 	(T::*fct)();
  };

  struct	ContainerArg
  {
    T *		obj;
    void 	(T::*fct)(Any);
    Any		arg;
  };

private:
  int					_ret;
  pthread_t				_thread;
  typename IThread<T>::STATUS		_status;
  struct Container			_container;
  struct ContainerArg			_containerArg;

  static void *				_threadEntryArg(void* args)
  {
    Thread<T>::ContainerArg *	containerArg = reinterpret_cast<Thread<T>::ContainerArg*>(args);

    (containerArg->obj->*(containerArg->fct))(containerArg->arg);
    return (NULL);
  }

  static void *				_threadEntry(void* args)
  {
    Thread<T>::Container *	container = reinterpret_cast<Thread<T>::Container*>(args);

    (container->obj->*(container->fct))();
    return (NULL);
  }

};

#endif /* !UTHREAD_H_ */
