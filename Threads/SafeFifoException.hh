#ifndef SAFEFIFOEXCEPTION_H_
# define SAFEFIFOEXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>
# include <sstream>
# include <cstring>

# ifndef _WIN32
#  include <cerrno>
# endif

class SafeFifoException : public std::exception
{
public:
  SafeFifoException(const int error);
  SafeFifoException(const std::string &error);
  ~SafeFifoException() throw() {}

  const char* what() const throw();

private:
  void addError(const int error);
  std::string	_info;

};


#endif /* !SAFEFIFOEXCEPTION_H_ */
