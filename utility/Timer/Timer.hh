#ifndef TIMER_H_
# define TIMER_H_

# ifdef __linux__
#  include "UTimer.hh"
# elif _WIN32
#  include "WTimer.hh"
# endif /* !_WIN32 */

#endif /* !TIMER_H_ */
