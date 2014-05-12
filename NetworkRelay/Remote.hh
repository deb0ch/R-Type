#ifndef REMOTE_H_
# define REMOTE_H_

# include <string>
# include <vector>
# include "Socket.hh"
# include "IBuffer.hh"
# include "NetworkBuffer.hh"
# include "INetworkRelay.hh"

class Remote
{
public:
  Remote(ISocketTCP &, unsigned int = 0);
  virtual			~Remote();
  const ISocketTCP		&getTCPSocket() const;
  ISocketTCP			&getTCPSocket();
  const std::string		&getIP() const;
  int				getPort() const;
  unsigned int			getPrivateHash() const;
  void				setIP(const std::string &ip);
  void				setPort(const int);
  void				setPrivateHash(const unsigned int);
  std::vector<IBuffer *>	&getSendBufferUDP();
  std::vector<IBuffer *>	&getSendBufferTCP();
  // TODO:
  void				sendTCP(IBuffer *);
  void				sendUDP(IBuffer *);
  std::vector<IBuffer *>	&getRecvBufferUDP();
  std::vector<IBuffer *>	&getRecvBufferTCP();

  const std::string		&getRoom() const;
  void				setRoom(const std::string &);

  void				networkSendTCP();
  void				networkReceiveTCP(INetworkRelay &network);
  void				networkSendUDP(SocketUDP &udp);

protected:
  ISocketTCP			*_tcp;
  std::string			_ip;
  std::string			_room;
  int				_port;
  unsigned int			_private_hash;
  std::vector<IBuffer *>	_send_buffer_tcp;
  std::vector<IBuffer *>	_send_buffer_udp;
  NetworkBuffer			_temporary_tcp_buffer;
  std::vector<IBuffer *>	_recv_buffer_tcp;
  std::vector<IBuffer *>	_recv_buffer_udp;
};

#endif /* !REMOTE_H_ */
