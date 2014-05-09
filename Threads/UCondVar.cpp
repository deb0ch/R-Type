#ifdef __linux__
#include "UCondVar.hh"

CondVar::CondVar() {
  pthread_cond_init(&(this->cond), NULL);
}

CondVar::~CondVar() {
  pthread_cond_destroy(&(this->cond));
}

void CondVar::wait(Mutex *mutex)
{
  pthread_cond_wait(&(this->cond), &mutex->_mutex);
}

void CondVar::signal(void)
{
  pthread_cond_signal(&(this->cond));
}

void CondVar::broadcast(void)
{
  pthread_cond_broadcast(&(this->cond));
}
#endif
