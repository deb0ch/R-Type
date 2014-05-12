#ifndef		USOCKETUDP_H_
# define	USOCKETUDP_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "ISocketUDP.hh"

class SocketUDP : public ISocketUDP
{

public:
  virtual ~SocketUDP();
  SocketUDP();

public:
  virtual void		setBlocking(const bool blocking);
  virtual const bool	isBlocking() const;
  virtual const int		getHandle() const;

  virtual void	bind(const int port, const std::string &address = "");
  virtual int	send(const IBuffer &, const int address, const int port);
  virtual int	send(const IBuffer &, const std::string & address, const int port);
  virtual int	receive(IBuffer &, std::string& address, int& port);

  virtual void	close();
  virtual void	init();

private:
  SocketUDP(int socke);

private:
  SocketUDP(const SocketUDP &);
  SocketUDP &operator=(const SocketUDP &);

private:
  int	_socket;
  bool	_isBlocking;

};

#endif /* !USOCKETUDP_H_ */
