#ifndef DIRECTORYLISTER_H_
# define DIRECTORYLISTER_H_

#ifdef __linux__
	#include "UDirectoryLister.hh"
#elif _WIN32
	#include "WDirectoryLister.hh"
#endif

#endif /* !DIRECTORYLISTER_H_ */
