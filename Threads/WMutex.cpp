#ifdef _WIN32

# include "WMutex.hh"

// Public

void	Mutex::lock()
{
	if ((_ret = WaitForSingleObject(_mutexHandle, INFINITE)) == WAIT_FAILED)
		throw ThreadException(ThreadException::MUTEX, GetLastError(), ThreadException::S_WARNING);
	_status = LOCKED;
}

void	Mutex::trylock()
{
	if ((_ret = WaitForSingleObject(_mutexHandle, 0)) == WAIT_FAILED)
		throw ThreadException(ThreadException::MUTEX, GetLastError(), ThreadException::S_WARNING);
	_status = LOCKED;
}

void	Mutex::unlock()
{
	if (ReleaseMutex(_mutexHandle) == false)
		throw ThreadException(ThreadException::MUTEX, GetLastError(), ThreadException::S_ERROR);
	_status = UNLOCKED;
}

IMutex::STATUS	Mutex::status() const
{
	return (_status);
}

Mutex::Mutex()
: _ret(0), _status(UNLOCKED)
{
	if ((_mutexHandle = CreateMutex(NULL, false, NULL)) == NULL)
		throw ThreadException(ThreadException::MUTEX, GetLastError(), ThreadException::S_ERROR);
}

Mutex::~Mutex()
{
	if (CloseHandle(_mutexHandle) == false)
		throw ThreadException(ThreadException::MUTEX, GetLastError(), ThreadException::S_ERROR);
}

// Private

#endif /* !_WIN32 */
