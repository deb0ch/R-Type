#ifdef _WIN32

# include "Timer.hh"

// Public:

Timer::Timer(unsigned long fps)
  : _fps(fps)
{
  _previousTime = this->getTime();
  _currentTime = this->getTime();
}

void	Timer::startFrame()
{
  _currentTime = this->getTime();
}

void	Timer::endFrame()
{
  if (!this->canTick())
    this->sleep((1000000 / _fps) - (_currentTime - _previousTime));
  else
    _previousTime = _currentTime;
}

bool	Timer::canTick() const
{
  return (_currentTime - _previousTime >= 1000000 / _fps);
}

unsigned long	Timer::getFps() const
{
  return (_fps);
}

unsigned long	Timer::getCurrentFps() const
{
  return (1000000 / (_currentTime - _previousTime));
}

void	Timer::setFps(unsigned long fps)
{
  _fps = fps;
}

unsigned long	Timer::getDeltaTime() const
{
  return (_currentTime - _previousTime);
}

unsigned long	Timer::getTime()
{
  if (clock_gettime(CLOCK_MONOTONIC, &_timeBuff) == -1)
    throw RTException("clock_gettime error: " + std::string(strerror(errno)));
  return (bufToTime(_timeBuff));
}

void	Timer::sleep(unsigned long delay) const
{
if (usleep(delay) == -1)
  throw RTException("usleep error: " + std::string(strerror(errno)));
}

// Private:

inline unsigned long	Timer::bufToTime(const struct timespec & timeBuff) const
{
	return ((timeBuff.tv_sec * 1000000) + (timeBuff.tv_nsec / 1000));
}

#endif /* !_WIN32 */