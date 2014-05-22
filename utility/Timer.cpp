
#include <iostream>
#include "Timer.hh"

// Public:

Timer::Timer()
{
  if (clock_gettime(CLOCK_MONOTONIC, &_timeBuff) == -1)
    throw RTException("clock_gettime error during Timer construction: "
		    + std::string(strerror(errno)));
  _milliTimeZero = bufToMilliTime(_timeBuff);
}

unsigned long	Timer::getMilliTime()
{
  if (clock_gettime(CLOCK_MONOTONIC, &_timeBuff) == -1)
    throw RTException("clock_gettime error: " + std::string(strerror(errno)));
  return (bufToMilliTime(_timeBuff) - _milliTimeZero);
}

void		Timer::milliSleep(unsigned long delay) const
{
  if (usleep(delay * 1000) == -1)
    throw RTException("usleep error: " + std::string(strerror(errno)));
}

// Private:

inline long	Timer::bufToMilliTime(const struct timespec & timeBuff) const
{
  return (timeBuff.tv_sec * 1000 + timeBuff.tv_nsec / 1000000);
}
