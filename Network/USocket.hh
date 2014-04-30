#ifndef		USOCKET_H_
# define	USOCKET_H_

#include "ISocket.hh"

class Socket : public ISocket
{
public :
  void init();
  void recieve();
  void send();
  void close();
};

#endif /* !USOCKET_H_ */
