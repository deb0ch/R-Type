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
  RTException(const int error, const std::string &prefix = "RTException : ");
  RTException(const std::string &error, const std::string &prefix = "RTException : ");
  ~RTException() throw() {}

  const char* what() const throw();

public:
  static void addClass(const std::string nameClass, const std::string msg);

private:
  void addError(const int error);
  std::string		_info;

};

#endif /* !RTEXCEPTION_H_ */
