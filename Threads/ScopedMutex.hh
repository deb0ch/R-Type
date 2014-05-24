#ifndef SCOPEDMUTEX_H_
# define SCOPEDMUTEX_H_

# include "IMutex.hh"

class ScopedMutex
{
private :
	IMutex *_mutex;

private:
	ScopedMutex() = delete;
	ScopedMutex(const ScopedMutex & other) = delete;
	ScopedMutex &operator=(const ScopedMutex & other) = delete;

public:
	ScopedMutex(IMutex *mutex);
	~ScopedMutex();
};

#endif /* !SCOPEDMUTEX_H_ */
