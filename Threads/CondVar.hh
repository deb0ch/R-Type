#ifndef CONDVAR_H_
# define CONDVAR_H_

# ifdef _WIN32
#  include "WCondVar.hh"
# elif __linux__
#  include "UCondVar.hh"
# endif

#endif /* !CONDVAR_H_ */
