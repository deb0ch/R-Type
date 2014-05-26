#ifndef TCPEXCEPTION_H_
# define TCPEXCEPTION_H_

# include "NetworkException.hh"

class TCPException : public NetworkException
{

public:
  TCPException(const int error);
  TCPException(const std::string &error);
  ~TCPException() throw() {}

};

#endif /* !TCPEXCEPTION_H_ */
