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
  enum	SEVERITY {
    S_FATAL,
    S_ERROR,
    S_WARNING
  };

public:
  RTException(const std::string type, const int error,
		   const RTException::SEVERITY severity);
  RTException(const std::string type, const std::string &error,
		   const RTException::SEVERITY severity);
  ~RTException() throw() {}

  const RTException::SEVERITY getSeverity() const;
  const char* what() const throw();

public:
  static void addClass(const std::string nameClass, const std::string msg);

private:
  static std::map<const std::string, std::string> _msg;
  void addError(const int error);
  std::string		_info;
  const std::string	_type;
  SEVERITY		_severity;

};

#endif /* !RTEXCEPTION_H_ */
