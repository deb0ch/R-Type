#ifndef THREADPOOL_H_
# define THREADPOOL_H_

#include <vector>
#include "IThread.hpp"
#include "Threads.hh"

template <typename T>
class ThreadPool
{
private :
	std::vector<IThread<T> > pool;

public :
	ThreadPool(int nb_thread);
};

#endif /* !THREADPOOL_H_ */