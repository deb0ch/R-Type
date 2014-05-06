#ifndef		LIBLOADEREXCEPTION_H_
# define	LIBLOADEREXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>

# ifndef _WIN32
#  include <cerrno>
#  include <cstdio>
#  include <cstring>
# endif

class LibLoaderException : public std::exception
{
public:
  LibLoaderException(const int error);
  LibLoaderException(const std::string &error);
  ~LibLoaderException() throw() {}

  const char* what() const throw();

private:
  void addError(const int error);
  std::string	_info;

};

#endif /* !LIBLOADEREXCEPTION_H_ */
