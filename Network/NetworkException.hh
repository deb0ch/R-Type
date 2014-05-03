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

  enum	SEVERITY {
    FATAL,
    ERROR,
    WARNING
  };

  static std::map<NetworkException::ERROR_TYPE, const std::string> _msg;

public:
  NetworkException(const NetworkException::ERROR_TYPE type, const int error,
		   const NetworkException::SEVERITY severity);
  NetworkException(const NetworkException::ERROR_TYPE type, const std::string &error,
		   const NetworkException::SEVERITY severity);
  ~NetworkException() throw() {}

  const NetworkException::SEVERITY getSeverity() const;
  const char* what() const throw();

private:
  void addError(const int error);
  std::string	_info;
  ERROR_TYPE	_type;
  SEVERITY	_severity;

};

#endif /* !NETWORKEXCEPTION_H_ */
