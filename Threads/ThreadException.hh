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

class	ThreadException : public std::exception
{
public:
  enum	ERROR_TYPE {
    NONE,
    THREAD,
    MUTEX
  };

  enum	SEVERITY {
    S_FATAL,
    S_ERROR,
    S_WARNING
  };

  static std::map<ThreadException::ERROR_TYPE, const std::string> _msg;

public:
	ThreadException(const ThreadException::ERROR_TYPE type, const int error,
			const ThreadException::SEVERITY severity);
	ThreadException(const ThreadException::ERROR_TYPE type, const std::string &error,
		  const ThreadException::SEVERITY severity);
	~ThreadException() throw() {}

  const ThreadException::SEVERITY getSeverity() const;
  const char* what() const throw();

private:
  void addError(const int error);
  std::string	_info;
  ERROR_TYPE	_type;
  SEVERITY	_severity;
};

#endif /* !THREADEXCEPTION_H_ */
