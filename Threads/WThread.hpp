#ifndef WTHREAD_H_
# define WTHREAD_H_

# include <windows.h>
# include <WinBase.h>
# include <processthreadsapi.h>
# include "IThread.hpp"
# include "Any.hpp"

template <typename T>
class Thread : public IThread<T>
{
	// Public
public:
  virtual void						start(T* obj, void (T::*fct)(Any), Any arg)
	{
		_container.obj = obj;
		_container.fct = fct;
		_container.arg = arg;
		if ((_threadHandle = CreateThread(
			NULL,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(_threadEntry),
			&_container,
			0,
			&_thread)) == NULL)
				throw ThreadException(GetLastError());
		_status = RUNNING;
	}

  virtual void				start(void* (*fct)(void*), void* arg)
  {
	  if ((_threadHandle = CreateThread(
		  NULL,
		  0,
		  reinterpret_cast<LPTHREAD_START_ROUTINE>(_threadEntry),
		  arg,
		  0,
		  &_thread)) == NULL)
		  throw ThreadException(GetLastError());
    this->_status = IThread<T>::RUNNING;
  }

	virtual void						exit()
	{
		ExitThread(0);
		_status = IThread::DEAD;
	}

	virtual void						wait()
	{
		if ((_ret = WaitForSingleObject(_threadHandle, INFINITE)) == WAIT_FAILED)
			throw ThreadException(GetLastError());
		_status = IThread::DEAD;
	}

	virtual typename IThread::STATUS	status() const
	{
		return (_status);
	}

	// Coplien
public:
	Thread() { _status = IThread::UNSTARTED; }
	virtual								~Thread() {}

	// Private
private:
	Thread(const Thread &) = delete;
	Thread &							operator=(const Thread &) = delete;

	// Attributes
private:
	DWORD								_ret;
	DWORD								_thread;
	HANDLE								_threadHandle;
	typename IThread::STATUS			_status;

private:
	struct		Container
	{
		T*		obj;
		void	(T::*fct)(Any);
		Any		arg;
	};
	struct Container					_container;

	// Private functions
	static void*						_threadEntry(void* args)
	{
		Thread<T>::Container*			container = reinterpret_cast<Thread<T>::Container*>(args);

		(container->obj->*(container->fct))(container->arg);
		return (NULL);
	}
};

#endif /* !WTHREAD_H_ */
