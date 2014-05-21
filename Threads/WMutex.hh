#ifndef WMUTEX_H_
# define WMUTEX_H_

# include <windows.h>
# include <WinBase.h>
# include <Synchapi.h>
# include "ThreadException.hh"
# include "IMutex.hh"

class Mutex : public IMutex
{
public:
	virtual void		lock();
	virtual bool		trylock();
	virtual void		unlock();
	virtual STATUS		status() const;

	PCRITICAL_SECTION	getCriticalSection();

public:
	Mutex();
	virtual				~Mutex();

private:
	Mutex(const Mutex & other) = delete;
	Mutex &				operator=(const Mutex & other) = delete;

private:
	STATUS				_status;
	CRITICAL_SECTION	_criticalSection;
};

#endif /* !WMUTEX_H_ */
