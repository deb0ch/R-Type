#ifndef RTEXCEPTION_H_
# define RTEXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>

# ifndef _WIN32
#  include <cerrno>
#  include <cstdio>
#  include <cstring>
# endif

class RTException : public std::exception
{
public:
  RTException(const int error);
  RTException(const std::string &error);
  ~RTException() throw() {}

public:
  RTException(const std::string &prefix, const int error);
  RTException(const std::string &prefix, const std::string &error);

  const char* what() const throw();

private:
  void addError(const int error);
  std::string		_info;
};

#endif /* !RTEXCEPTION_H_ */
