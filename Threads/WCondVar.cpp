#ifdef _WIN32
#include "WCondVar.hh"

//----- ----- Constructors ----- ----- //
CondVar::CondVar()
{
	InitializeConditionVariable(this->cond);
	//pthread_cond_init(&(this->cond), NULL);
}

CondVar::CondVar(const CondVar& ref)
{
	this->cond = ref.cond;
}

//----- ----- Destructor ----- ----- //
CondVar::~CondVar()
{
	//pthread_cond_destroy(&(this->cond));
}

//----- ----- Operators ----- ----- //
CondVar&	CondVar::operator=(const CondVar& ref)
{
	this->cond = ref.cond;
	return (*this);
}


void CondVar::wait(Mutex *mutex)
{
	PCRITICAL_SECTION test;
	SleepConditionVariableCS(this->cond, test, INFINITE);
	//pthread_cond_wait(&(this->cond), (const_cast<pthread_mutex_t *>(&(mutex->getMutex()))));
}

void CondVar::signal(void)
{
	//pthread_cond_signal(&(this->cond));
}

void CondVar::broadcast(void)
{
	//pthread_cond_broadcast(&(this->cond));
}
#endif