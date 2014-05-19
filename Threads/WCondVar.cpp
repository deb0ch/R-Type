#ifdef _WIN32
#include "WCondVar.hh"

//----- ----- Constructors ----- ----- //
CondVar::CondVar()
{
	// No errors specified in the man
	InitializeConditionVariable(&this->_cond);
}

CondVar::CondVar(const CondVar& ref)
{
	this->_cond = ref._cond;
}

//----- ----- Destructor ----- ----- //
CondVar::~CondVar() {}

//----- ----- Operators ----- ----- //
CondVar&	CondVar::operator=(const CondVar& ref)
{
	this->_cond = ref._cond;
	return (*this);
}

void CondVar::wait(Mutex *mutex)
{
	if (SleepConditionVariableCS(&this->_cond, mutex->getCriticalSection(), INFINITE) == 0)
		throw (MutexException(GetLastError()));
}

void CondVar::signal(void)
{
	// No errors specified in the man
	WakeConditionVariable(&_cond);
}

void CondVar::broadcast(void)
{
	// No errors specified in the man
	WakeAllConditionVariable(&_cond);
}
#endif