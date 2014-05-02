#include <errno.h>

#include "NetworkException.hh"
#include "Select.hh"

Select::Select(const int to)
{
  this->_reads = NULL;
  this->_writes = NULL;
  this->_to = new struct timeval();
  this->_to->tv_sec = to;
  this->maxFd = 0;
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
      throw NetworkException(NetworkException::SELECT, "Function select failed");
}

bool	Select::issetReads(const int fd)
{
  return (FD_ISSET(fd, this->_reads));
}

bool	Select::issetWrites(const int fd)
{
  return (FD_ISSET(fd, this->_writes));
}
