#ifndef SERVERRELAY_H_
# define SERVERRELAY_H_

# include <map>
# include "EventManager.hpp"
# include "Select.hh"
# include "NetworkInitializer.hh"
# include "Remote.hh"
# include "World.hh"
# include "RoomServer.hh"
# include "INetworkRelay.hh"

class ServerRelay : public INetworkRelay
{

public:
  ServerRelay(int port = 4011, int nb_pending_connection = 42);
  virtual		~ServerRelay();
  virtual bool		start();
  virtual void		start(Any);
  virtual Room		*getRoom(const std::string &room_name);
  virtual IBuffer	*getTCPBuffer();
  virtual IBuffer	*getUDPBuffer();
  virtual Remote	*getRemote(unsigned int) const;
  virtual Remote	*getRemote(const std::string &ip, const int port) const;
  virtual void		disposeUDPBuffer(IBuffer *);
  virtual void		disposeTCPBuffer(IBuffer *);

private:
  void			waitForEvent();
  void			addClient();
  unsigned int		generateHash() const;
  void			receiveUDP();
  void			removeRemote(Remote *remote);
  void			manageAllRemotes();
  void			manageRemotes(std::vector<Remote *> &remotes, Room *room = NULL);
  void			manageRemotesInRooms();
  bool			manageRemotesReceiveTCP(std::vector<Remote *> &remotes, Room *room,
						std::vector<Remote *>::iterator &it, Remote *remote);
  void			udpConnect(Remote *remote);

protected:
  NetworkInitializer			_network_initializer;
  SocketTCP				_server_socket_tcp;
  SocketUDP				_server_socket_udp;
  Select				_select;
  Mutex					_mutex_room;
  std::map<std::string, RoomServer*>	_rooms;
  std::vector<Remote *>			_remotsWithoutRoom;
  LockVector<IBuffer *>			_available_udp;
  LockVector<IBuffer *>			_available_tcp;

};

#endif /* !SERVERRELAY_H_ */
