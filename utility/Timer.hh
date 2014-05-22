#ifndef		TIMER_H_
# define	TIMER_H_

# define _XOPEN_SOURCE 700

# include <errno.h>
# include <exception>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include "RTException.hh"

class Timer
{
public:
  Timer();
  ~Timer() {}

public:
  unsigned long		getMilliTime();
  void			milliSleep(unsigned long delay) const;

private:
  struct timespec	_timeBuff;
  unsigned long		_milliTimeZero;

private:
  Timer(const Timer &) = delete;
  Timer &operator=(const Timer &) = delete;

  inline long		bufToMilliTime(const struct timespec & timebuff) const;
};

#endif /* !TIMER_H_ */
