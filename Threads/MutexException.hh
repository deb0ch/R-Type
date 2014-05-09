#ifndef MUTEXEXCEPTION_H_
# define MUTEXEXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>
# include <sstream>
# include <cstring>

# ifndef _WIN32
#  include <cerrno>
# endif

class MutexException : public std::exception
{
public:
  MutexException(const int error);
  MutexException(const std::string &error);
  ~MutexException() throw() {}

  const char* what() const throw();

private:
  void addError(const int error);
  std::string	_info;

};


#endif /* !MUTEXEXCEPTION_H_ */
