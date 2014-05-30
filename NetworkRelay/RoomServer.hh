#ifndef ROOMSERVER_H_
# define ROOMSERVER_H_

#include "Room.hh"

class ServerRelay;

class RoomServer : public Room
{
public:
  RoomServer(ServerRelay *server, const std::string &nameRoomServer);
  virtual			~RoomServer();
  virtual void			removeRemote(Remote *remote);
  void				addRemote(Remote *remote);
  RunWorldServer		&getRunWorldServer();

private:
  RoomServer() = delete;
  RoomServer(const RoomServer &) = delete;
  RoomServer &operator=(const RoomServer &) = delete;

protected:
  ServerRelay		*_serverRelay;
  std::string		_nameRoomServer;
  RunWorldServer	*_runWorldServer;
  Thread<RunWorldServer> *_thread;

};

#endif /* !ROOMSERVER_H_ */
