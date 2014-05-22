#include <errno.h>

#include "SelectException.hh"
#include "Select.hh"

Select::Select(const int to, const int tu)
{
  this->_reads = NULL;
  this->_writes = NULL;
  this->_to = new struct timeval();
  this->_to->tv_sec = to;
  this->_to->tv_usec = tu;
  this->maxFd = 0;
}

Select::Select()
{
  this->_reads = NULL;
  this->_writes = NULL;
  this->_to->tv_sec = 0;
  this->_to->tv_usec = 0;
  this->maxFd = 0;
}

void	Select::setTimeOut(const int to, const int tu)
{
  if (!this->_to)
    this->_to = new struct timeval();
  this->_to->tv_sec = to;
  this->_to->tv_usec = tu;
}

void	Select::doSelect()
{
  int	ret;

  while ((ret = select(this->maxFd + 1, this->_reads, this->_writes, NULL, this->_to)) == -1 &&
	 errno == EINTR)
    {
      if (ret == -1 && errno != EINTR)
	throw SelectException("Function select failed");
    }
}

bool	Select::issetReads(const int fd)
{
  return (FD_ISSET(fd, this->_reads) != 0);
}

bool	Select::issetWrites(const int fd)
{
  return (FD_ISSET(fd, this->_writes) != 0);
}

void	Select::initReads()
{
  this->_reads = new fd_set();
  FD_ZERO(this->_reads);
}

void	Select::initWrites()
{
  this->_writes = new fd_set();
  FD_ZERO(this->_writes);
}

void	Select::addRead(int handle)
{
  if (handle > this->maxFd)
    this->maxFd = handle;
  FD_SET(handle, this->_reads);
}

void	Select::addWrite(int handle)
{
  if (handle > this->maxFd)
    this->maxFd = handle;
  FD_SET(handle, this->_writes);
}

void	Select::removeRead(int handle)
{
  FD_CLR(handle, this->_reads);
}

void	Select::removeWrite(int handle)
{
  FD_CLR(handle, this->_writes);
}

void	Select::reset()
{
  this->maxFd = 0;
  FD_ZERO(this->_reads);
  FD_ZERO(this->_writes);
}
