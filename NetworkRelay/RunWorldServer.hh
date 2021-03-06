#ifndef RUNWORLDSERVER_H_
# define RUNWORLDSERVER_H_

#include	"World.hh"
#include	"Timer.hh"
#include	"Any.hpp"

class ServerRelay;

class RunWorldServer
{

public:
  RunWorldServer(ServerRelay *server, const std::string &nameRoom);
  virtual ~RunWorldServer();
  void run(Any);
  void run();
  World *getWorld();
  const World *getWorld() const;
  void isEnd(bool isEnd);

private:
  void addSystems();
  void addSharedObjetcs();
  void addEntities();

private:
  RunWorldServer() = delete;
  RunWorldServer(const RunWorldServer &);
  RunWorldServer &operator=(const RunWorldServer &);

protected:
  ServerRelay *_server;
  World *_world;
  Timer _timer;
  std::string _nameRoom;
  bool _isEnd;

};

#endif /* !RUNWORLDSERVER_H_ */
