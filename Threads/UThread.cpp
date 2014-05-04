# include "UThread.hh"

// Public
void	UThread::start(void* arg, void* (*fct)(void*))
{
  if ((_ret = pthread_create(&_thread, NULL, fct, arg)) != 0)
    throw ThreadException(ThreadException::THREAD, _ret, ThreadException::S_ERROR);
}

void	UThread::exit()
{
  pthread_exit(NULL);
  _status = DEAD;
}

void	UThread::join()
{
  if ((_ret = pthread_join(_thread, NULL)) != 0)
    throw ThreadException(ThreadException::THREAD, _ret, ThreadException::S_ERROR);
  _status = DEAD;
}

IThread::STATUS	UThread::status() const
{
  return (_status);
}

UThread::UThread()
{
  _status = UNSTARTED;
}

UThread::~UThread()
{}

// Private
