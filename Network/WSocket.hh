#ifndef		WSOCKET_H_
# define	WSOCKET_H_

#include "ISocket.hh"

class Socket : public ISocket
{
public :
  void init();
  void recieve();
  void send();
  void close();
};

#endif /* !WSOCKET_H_ */
