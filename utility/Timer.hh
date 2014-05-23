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
  void			startFrame();
  void			endFrame();
  bool			canTick() const;
  float			getDeltaTime() const;

  int			getFps() const;
  float			getCurrentFps() const;
  void			setFps(int fps);

  float			getTime();
  void			sleep(float delay) const;

public:
  Timer(int fps = 60);
  ~Timer() {}

private:
  Timer(const Timer &) = delete;
  Timer &operator=(const Timer &) = delete;

private:
  inline float		bufToTime(const struct timespec & timebuff) const;

private:
  int			_fps;
  struct timespec	_timeBuff;
  float			_timeZero;
  float			_currentTime;
  float			_previousTime;
};

#endif /* !TIMER_H_ */
