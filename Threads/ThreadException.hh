#ifndef THREADEXCEPTION_H_
# define THREADEXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>
# include <sstream>
# include <cstring>

# ifndef _WIN32
#  include <cerrno>
# endif

class ThreadException : public std::exception
{
public:
  ThreadException(const int error);
  ThreadException(const std::string &error);
  ~ThreadException() throw() {}

  const char* what() const throw();

private:
  void addError(const int error);
  std::string	_info;

};

#endif /* !THREADEXCEPTION_H_ */
