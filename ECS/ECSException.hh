#ifndef ECSEXCEPTION_H_
# define ECSEXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>

# ifndef _WIN32
#  include <cerrno>
#  include <cstdio>
#  include <cstring>
# endif

class ECSException : public std::exception
{
public:
  ECSException(const int error);
  ECSException(const std::string &error);
  ECSException(const std::string &prefix, const int error);
  ECSException(const std::string &prefix, const std::string &error);
  ~ECSException() throw() {}

protected:

  const char* what() const throw();

private:
  void addError(const int error);
  std::string		_info;
};


#endif /* !ECSEXCEPTION_H_ */
