#ifndef CLIENTRELAY_H_
# define CLIENTRELAY_H_

# include "Socket.hh"
# include "Select.hh"
# include "NetworkInitializer.hh"
# include "INetworkRelay.hh"
# include "Remote.hh"
# include "Room.hh"

class ClientRelay : public INetworkRelay
{
public:
  ClientRelay(const std::string &ip, const int port = 42);
  virtual				~ClientRelay();
  virtual void				start();
  virtual void				start(Any);
  virtual Room				*getRoom(const std::string &room_name);
  virtual IBuffer			*getTCPBuffer();
  virtual IBuffer			*getUDPBuffer();
  virtual Remote			*getRemote(unsigned int);
  virtual Remote			*getRemote(const std::string &ip, const int port);
  virtual void				disposeUDPBuffer(IBuffer *);
  virtual void				disposeTCPBuffer(IBuffer *);

private:
  void					waitForEvent();
  void					udpConnect();

protected:
  NetworkInitializer			_network_initializer;
  SocketUDP				_socket_udp;
  Select				_select;
  Room					_room;
  Remote				*_remote;
  SafeFifo<IBuffer *>			_available_udp;
  SafeFifo<IBuffer *>			_available_tcp;
};

#endif /* !CLIENTRELAY_H_ */