#ifndef SELECT_HH
# define SELECT_HH

#include <sys/types.h>
#ifdef _WIN32
	#include <Windows.h>
#elif
	#include <sys/time.h>
	#include <unistd.h>
#endif

class			Select
{

private:

  fd_set		*_reads;
  fd_set		*_writes;
  struct timeval	*_to;
  int			maxFd;

public:

  Select(const int to = 1);
  ~Select() {}

  template <typename T>
  void	initReads(T const &container)
  {
    int	tmp;

    this->_reads = new fd_set();
    FD_ZERO(this->_reads);
    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
      {
	tmp = (*it)->getHandle();
	if (tmp > this->maxFd)
	  this->maxFd = tmp;
	FD_SET(tmp, this->_reads);
      }
  }

  template <typename T>
  void	initWrites(T const &container)
  {
    int	tmp;

    this->_writes = new fd_set();
    FD_ZERO(this->_writes);
    for (typename T::const_iterator it = container.begin(); it != container.end(); ++it)
      {
	tmp = (*it)->getHandle();
	if (tmp > this->maxFd)
	  this->maxFd = tmp;
	FD_SET(tmp, this->_writes);
      }
  }

  void	setTimeOut(const int);
  void	doSelect();
  bool	issetReads(const int);
  bool	issetWrites(const int);

};

#endif /* !SELECT_HH */
