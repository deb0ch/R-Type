#ifdef _WIN32

# include "WMutex.hh"

// Public

void	Mutex::lock()
{
	// This can raise EXCEPTION_POSSIBLE_DEADLOCK. Winapi recommends not to handle this exception.
	EnterCriticalSection(&_criticalSection);
	_status = LOCKED;
}

bool	Mutex::trylock()
{
	_status = LOCKED;
	return (TryEnterCriticalSection(&_criticalSection)); // cannot fail. No exceptions.
}

void	Mutex::unlock()
{
	LeaveCriticalSection(&_criticalSection);
	_status = UNLOCKED;
}

IMutex::STATUS	Mutex::status() const
{
	return (_status);
}

PCRITICAL_SECTION	Mutex::getCriticalSection()
{
	return (&_criticalSection);
}

Mutex::Mutex()
: _status(UNLOCKED)
{
	InitializeCriticalSection(&_criticalSection); // cannot fail. No return value, no exceptions.
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&_criticalSection); // cannot fail. No return value, no exceptions.
}

// Private

#endif /* !_WIN32 */
