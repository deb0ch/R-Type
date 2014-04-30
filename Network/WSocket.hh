#ifndef		WSOCKET_H_
# define	WSOCKET_H_

class Socket : public ISocket
{
public :
  void init();
  void recieve();
  void send();
  void close();
};

#endif /* !WSOCKET_H_ */
