#ifndef SERVERRELAY_H_
# define SERVERRELAY_H_

# include <map>
# include "EventManager.hpp"
# include "INetworkRelay.hh"
# include "Select.hh"
# include "NetworkInitializer.hh"
# include "Remote.hh"
# include "Room.hh"
# include "World.hh"

class ServerRelay : public INetworkRelay
{
private:
public:
  // World * is temporary, we will need to create a new world each time we create a room
  ServerRelay(World *, int port = 4011, int nb_pending_connection = 42);
  virtual				~ServerRelay();
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
  void					addClient();
  unsigned int				generateHash();
  void					receiveUDP();
  void					removeRemote(Remote *remote);
  void					manageRemotes();
  void					udpConnect(Remote *remote);

protected:
  NetworkInitializer			_network_initializer;
  SocketTCP				_server_socket_tcp;
  SocketUDP				_server_socket_udp;
  Select				_select;
  std::vector<Remote *>			_disonnect_remotes;
  Mutex					_mutex_room;
  std::map<std::string, Room>		_remotes;
  SafeFifo<IBuffer *>			_available_udp;
  SafeFifo<IBuffer *>			_available_tcp;
  // temporary
  World					*_world;
};

#endif /* !SERVERRELAY_H_ */
