#ifndef RUNWORLDSERVER_H_
# define RUNWORLDSERVER_H_

#include	"ServerRelay.hh"
#include	"World.hh"

class RunWorldServer
{

public:
  RunWorldServer(ServerRelay *server, const std::string &nameRoom);
  virtual ~RunWorldServer();
  void run();

private:
  void addSystems();
  void addSharedObjetcs();
  void addEntities(World &world)

private:
  RunWorldServer() = delete;
  RunWorldServer(const RunWorldServer &);
  RunWorldServer &operator=(const RunWorldServer &);

protected:
  ServerRelay *_server;
  World _world;
  Timer _timer;
  std::string _nameRoom;

};

#endif /* !RUNWORLDSERVER_H_ */
