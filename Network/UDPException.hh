#ifndef UDPEXCEPTION_H_
# define UDPEXCEPTION_H_

# include "NetworkException.hh"

class UDPException : public NetworkException
{

public:
  UDPException(const int error);
  UDPException(const std::string &error);
  ~UDPException() throw() {}

};


#endif /* !UDPEXCEPTION_H_ */
