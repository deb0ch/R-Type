#ifndef UTIMER_H_
# define UTIMER_H_

# define _XOPEN_SOURCE 700

# ifdef __linux__
#  include <errno.h>
#  include <exception>
#  include <unistd.h>
# endif /* !__linux__ */

# ifdef _win32

# endif /* !_WIN32 */

# include <string>
# include <time.h>

# include "ITimer.hh"
# include "RTException.hh"

/**
 * All time units in this class are in microseconds
*/
class Timer : public ITimer
{
public:
  virtual void			startFrame();
  virtual void			endFrame();
  virtual bool			canTick() const;
  virtual float			getDeltaTime() const;

  virtual unsigned long		getFps() const;
  virtual unsigned long		getCurrentFps() const;
  virtual void			setFps(unsigned long fps);

  virtual unsigned long		getTime();
  virtual void			sleep(unsigned long delay) const;

public:
  Timer(unsigned long fps = 60);
  virtual ~Timer() {}

private:
  Timer(const Timer &) = delete;
  Timer &operator=(const Timer &) = delete;

private:
  inline unsigned long	bufToTime(const struct timespec & timebuff) const;

private:
  unsigned long		_fps;
  struct timespec	_timeBuff;
  unsigned long		_timeZero;
  unsigned long		_currentTime;
  unsigned long		_previousTime;
};

#endif /* !UTIMER_H_ */
