#ifdef __linux__
#include "UCondVar.hh"

//----- ----- Constructors ----- ----- //
CondVar::CondVar()
{
  pthread_cond_init(&(this->cond), NULL);
}

CondVar::CondVar(const CondVar& ref)
{
  this->cond = ref.cond;
}

//----- ----- Destructor ----- ----- //
CondVar::~CondVar()
{
  pthread_cond_destroy(&(this->cond));
}

//----- ----- Operators ----- ----- //
CondVar&	CondVar::operator=(const CondVar& ref)
{
  this->cond = ref.cond;
  return (*this);
}

//----- ----- Getters ----- ----- //
pthread_cond_t	CondVar::getCond() const
{
  return (this->cond);
}

//----- ----- Setters ----- ----- //
void	CondVar::setCond(pthread_cond_t cond)
{
  this->cond = cond;
}

void CondVar::wait(Mutex *mutex)
{
  pthread_cond_wait(&(this->cond), (const_cast<pthread_mutex_t *>(&(mutex->getMutex()))));
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
