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
  enum	ERROR_TYPE {
    NONE,
    SELECT,
    UDP,
    TCP
  };

  static std::map<NetworkException::ERROR_TYPE, const std::string> _msg;

public:
  NetworkException(const NetworkException::ERROR_TYPE type, const int error);
  NetworkException(const NetworkException::ERROR_TYPE type, const std::string &error);
  ~NetworkException() throw() {}
  const char* what() const throw();

private:
  std::string	_info;
  ERROR_TYPE	_type;

};

#endif /* !NETWORKEXCEPTION_H_ */
