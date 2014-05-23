
#include <iostream>
#include "Timer.hh"

// Public:

Timer::Timer(int fps)
  : _fps(fps)
{
  if (clock_gettime(CLOCK_MONOTONIC, &_timeBuff) == -1)
    throw RTException("clock_gettime error during Timer construction: "
		    + std::string(strerror(errno)));
  _timeZero = this->bufToTime(_timeBuff);
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
    this->sleep((1.f / _fps) - (_currentTime - _previousTime));
  else
    _previousTime = _currentTime;
}

bool	Timer::canTick() const
{
  return (_currentTime - _previousTime >= 1.f / _fps);
}

int	Timer::getFps() const
{
  return (_fps);
}

float	Timer::getCurrentFps() const
{
  return (1.f / (_currentTime - _previousTime));
}

void	Timer::setFps(int fps)
{
  _fps = fps;
}

float	Timer::getDeltaTime() const
{
  return (_currentTime - _previousTime);
}

float	Timer::getTime()
{
  if (clock_gettime(CLOCK_MONOTONIC, &_timeBuff) == -1)
    throw RTException("clock_gettime error: " + std::string(strerror(errno)));
  return (bufToTime(_timeBuff) - _timeZero);
}

void	Timer::sleep(float delay) const
{
  if (usleep(delay) == -1)
    throw RTException("usleep error: " + std::string(strerror(errno)));
}

// Private:

inline float	Timer::bufToTime(const struct timespec & timeBuff) const
{
  return (timeBuff.tv_sec + timeBuff.tv_nsec / 1000000000.f);
}
