#ifndef REMOTE_H_
# define REMOTE_H_

# include <string>
# include <vector>
# include "Socket.hh"
# include "IBuffer.hh"
# include "NetworkBuffer.hh"
# include "INetworkRelay.hh"
# include "SafeFifo.hpp"
# include "LockVector.hpp"

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
  void				sendTCP(IBuffer *);
  void				sendUDP(IBuffer *);
  LockVector<IBuffer *>		&getRecvBufferUDP();
  LockVector<IBuffer *>		&getRecvBufferTCP();

  const std::string		&getRoom() const;
  void				setRoom(const std::string &);

  void				networkSendTCP(INetworkRelay &network);
  bool				networkReceiveTCP(INetworkRelay &network);
  void				networkSendUDP(INetworkRelay &network, SocketUDP &udp);

  void				setReady(bool ready);
  bool				isReady() const;

  bool				canSendUDP();
  bool				canSendTCP();

private:
  bool				extractTCPPacket(INetworkRelay &);

protected:
  ISocketTCP			*_tcp;
  std::string			_ip;
  std::string			_room;
  int				_port;
  unsigned int			_private_hash;
  LockVector<IBuffer *>		_send_buffer_tcp;
  LockVector<IBuffer *>		_send_buffer_udp;
  NetworkBuffer			_temporary_tcp_buffer;
  LockVector<IBuffer *>		_recv_buffer_tcp;
  LockVector<IBuffer *>		_recv_buffer_udp;
  bool				_ready;

};

#endif /* !REMOTE_H_ */
