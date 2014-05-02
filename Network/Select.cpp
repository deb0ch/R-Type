#include <errno.h>

#include "Select.hh"

Select::Select(const int to)
{
  this->_readss = new fd_set();
  this->_writes = new fd_set();
  this->_to = new struct timeval();
  this->_to->tv_sec = to;
  this->maxFd = 0;
}

template <class T>
void	Select::initReads(T<int> const &container)
{
  int	tmp;

  FD_ZERO(this->_reads);
  for (T<int>::iterator it = container.begin() ; it != container.end(); ++it)
    {
      tmp = (*it).getHandle();
      if (tmp > this->maxFd)
	this->maxFd = tmp;
      FD_SET(tmp, this->_reads);
    }
}

template <class T>
void	Select::initWrites(T<int> const &container)
{
  FD_ZERO(this->_writes);
  for (T<int>::iterator it = container.begin() ; it != container.end(); ++it)
    {
      tmp = (*it).getHandle();
      if (tmp > this->maxFd)
	this->maxFd = tmp;
      FD_SET(tmp, this->_writes);
    }
}

void	Select::setTimeOut(const int to)
{
  this->_to->tv_sec = to;
}

void	Select::doSelect()
{
  int	ret;

  while ((ret = select(this->maxFd + 1, this->_reads, this->_writes, NULL, this->_to)) == -1 &&
	 errno == EINTR)
    if (ret == -1 && errno != EINTR)
      throw 2;
}

bool	Select::issetReads(const int fd)
{
  return (FD_ISSET(fd, this->_reads));
}

bool	Select::issetWrites(const int fd)
{
  return (FD_ISSET(fd, this->_writes));
}
