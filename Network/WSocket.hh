#ifndef		WSOCKET_H_
# define	WSOCKET_H_

#include <windows.h>
#include <winsock.h>
#include "ISocket.hh"

class Socket : public ISocket
{
protected :
	SOCKET socket;
	WSADATA wsaData;

public :
  void init();
  void recieve();
  void send();
  void close();
};

#endif /* !WSOCKET_H_ */
