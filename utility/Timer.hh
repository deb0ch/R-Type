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
  void			setDelta();
  unsigned long		getDelta() const;
  unsigned long		getMilliTime();
  void			milliSleep(unsigned long delay) const;

public:
  Timer();
  ~Timer() {}

private:
  Timer(const Timer &) = delete;
  Timer &operator=(const Timer &) = delete;

private:
  inline long		bufToMilliTime(const struct timespec & timebuff) const;

private:
  struct timespec	_timeBuff;
  unsigned long		_milliTimeZero;
};

#endif /* !TIMER_H_ */
