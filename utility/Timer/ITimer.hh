#ifndef ITIMER_H_
# define ITIMER_H_

# include "RTException.hh"

/**
 * All time units in this class are in microseconds
*/
class ITimer
{
public:
  virtual void					startFrame() = 0;
  virtual void					endFrame() = 0;
  virtual bool					canTick() const = 0;
  virtual unsigned long			getDeltaTime() const = 0;

  virtual unsigned long			getFps() const = 0;
  virtual unsigned long			getCurrentFps() const = 0;
  virtual void					setFps(unsigned long fps) = 0;

  virtual unsigned long			getTime() = 0;
  virtual void					sleep(unsigned long delay) const = 0;

public:
	virtual ~ITimer() {}
};

#endif /* !ITIMER_H_ */
