#ifndef		NETWORKEXCEPTION_H_
# define	NETWORKEXCEPTION_H_

# include <exception>
# include <iostream>
# include <map>

# ifndef _WIN32
#  include <cerrno>
#  include <cstdio>
#  include <cstring>
# endif

class NetworkException : public std::exception
{
public:
  NetworkException(const int error);
  NetworkException(const std::string &error);
  ~NetworkException() throw() {}

protected:
  NetworkException(const std::string &prefix, const int error);
  NetworkException(const std::string &prefix, const std::string &error);

  const char* what() const throw();

private:
  void addError(const int error);
  std::string	_info;

};

#endif /* !NETWORKEXCEPTION_H_ */
