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
    this->sleep((CLOCKS_PER_SEC / _fps) - (_currentTime - _previousTime));
  else
    _previousTime = _currentTime;
}

bool	Timer::canTick() const
{
  return (_currentTime - _previousTime >= CLOCKS_PER_SEC / _fps);
}

float	Timer::getDeltaTime() const
{
  return ((_currentTime - _previousTime) / 1000.f);
}

unsigned long	Timer::getFps() const
{
  return (_fps);
}

unsigned long	Timer::getCurrentFps() const
{
  return (CLOCKS_PER_SEC / (_currentTime - _previousTime));
}

void	Timer::setFps(unsigned long fps)
{
  _fps = fps;
}

unsigned long	Timer::getTime()
{
  if ((_time = clock()) == static_cast<clock_t>(-1))
    throw RTException(GetLastError());
  return (_time);
}

void	Timer::sleep(unsigned long delay) const
{
  Sleep(delay); // No error return or exception
}

// Private:

#endif /* !_WIN32 */
