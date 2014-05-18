#ifdef _WIN32

# include "WMutex.hh"
# include "MutexException.hh"

// Public

void	Mutex::lock()
{
	if ((_ret = WaitForSingleObject(_mutexHandle, INFINITE)) == WAIT_FAILED)
		throw MutexException(GetLastError());
	_status = LOCKED;
}

bool	Mutex::trylock()
{
	if ((_ret = WaitForSingleObject(_mutexHandle, 0)) == WAIT_FAILED)
		throw MutexException(GetLastError());
	if (_ret == WAIT_OBJECT_0)
	  {
	    _status = LOCKED;
	    return (true);
	  }
	else
	  return (false);
}

void	Mutex::unlock()
{
	if (ReleaseMutex(_mutexHandle) == false)
		throw MutexException(GetLastError());
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
		throw MutexException(GetLastError());
}

Mutex::~Mutex()
{
	if (CloseHandle(_mutexHandle) == false)
		throw MutexException(GetLastError());
}

// Private

#endif /* !_WIN32 */
