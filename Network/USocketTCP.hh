#ifndef		USOCKETTCP_H_
# define	USOCKETTCP_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "ISocketTCP.hh"

class SocketTCP : public ISocketTCP
{

public:
  virtual ~SocketTCP();
  SocketTCP();

public:
  virtual ISocketTCP	*accept();
  virtual void		listen(const std::size_t block);
  virtual void		bind(int port, const std::string & address = "");
  virtual const int		getHandle() const;

  virtual void setBlocking(const bool blocking);
  virtual const bool isBlocking() const;
  virtual void close();
  virtual void init();

  virtual void connect(const std::string &address, const int port);
  virtual void connect(const int address, const int port);
  virtual int send(const void* data, const std::size_t size);
  virtual int receive(void* data, const std::size_t size);

private:
  SocketTCP(int socke);

private:
  SocketTCP(const SocketTCP &);
  SocketTCP &operator=(const SocketTCP &);

private:
  int	_socket;
  bool	_isBlocking;
};


#endif /* !USOCKETTCP_H_ */
