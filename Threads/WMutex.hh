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
	virtual void		trylock();
	virtual void		unlock();
	virtual STATUS	status() const;

public:
	Mutex();
	virtual		~Mutex();

private:
	Mutex(const Mutex & other) = delete;
	Mutex &		operator=(const Mutex & other) = delete;

private:
	int			_ret;
	STATUS		_status;
	HANDLE		_mutexHandle;
};

#endif /* !WMUTEX_H_ */
