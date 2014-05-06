#ifndef SELECTEXCEPTION_H_
# define SELECTEXCEPTION_H_

# include "NetworkException.hh"

class SelectException : public NetworkException
{

public:
  SelectException(const int error);
  SelectException(const std::string &error);
  ~SelectException() throw() {}

};


#endif /* !SELECTEXCEPTION_H_ */
