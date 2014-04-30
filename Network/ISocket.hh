#ifndef		ISOCKET_H_
# define	ISOCKET_H_

class ISocket
{
public :
  virtual void init() = 0;
  virtual void recieve() = 0;
  virtual void send() = 0;
  virtual void close() = 0;
};

#endif /* !ISOCKET_H_ */
