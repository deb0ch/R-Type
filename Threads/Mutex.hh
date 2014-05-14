#ifndef MUTEX_H_
# define MUTEX_H_

# ifdef _WIN32
#  include "WMutex.hh"
# elif __linux__
#  include "UMutex.hh"
# endif

#endif /* !MUTEX_H_ */
