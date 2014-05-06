#ifndef		WSOCKETUDP_H_
# define	WSOCKETUDP_H_

# include <Windows.h>
# include <string>
# include "ISocketUDP.hh"
# include "IBuffer.hh"

class SocketUDP : public ISocketUDP
{
private:
	SOCKET socket;
	WSADATA wsaData;
	bool blockSocket;
	struct sockaddr_in clientService;

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
  SocketUDP(const SOCKET & sock);
  SocketUDP(const SocketUDP &);
  SocketUDP &operator=(const SocketUDP &);

};

#endif /* !WSOCKETUDP_H_ */
