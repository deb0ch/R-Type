#ifndef SELECT_HH
# define SELECT_HH

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

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

  template <class T>
  void initReads(T<int> const &);

  template <class T>
  void initWrites(T<int> const &);

  void	setTimeOut(const int);
  void	doSelect();
  bool	issetReads(const int);
  bool	issetWrites(const int);

};

#endif /* !SELECT_HH */
