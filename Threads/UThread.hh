#ifndef UTHREAD_H_
# define UTHREAD_H_

# include "IThread.hh"
# include "../ECS/Any.hpp"

class UThread : public IThread
{
public:
  virtual void			start(void* arg, void* (*fct)(void*));
  virtual void			exit();
  virtual void			join();
  virtual IThread::STATUS	status() const;

public:
				UThread();
  virtual			~UThread();

private:
				UThread(const UThread &) = delete;
  UThread &			operator=(const UThread &) = delete;

private:
  int				_ret;
  pthread_t			_thread;
  IThread::STATUS		_status;
};

#endif /* !UTHREAD_H_ */
