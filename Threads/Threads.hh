#ifndef THREADS_H_
# define THREADS_H_

#ifdef __linux__
	#include "UThread.hpp"
	#include "UMutex.hh"
#elif _WIN32
	#include "WThread.hpp"
	#include "WMutex.hh"
#endif

#include "ScopedMutex.hh"

#endif /* !THREADS_H_ */
