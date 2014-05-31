#include <algorithm>
#include "NewPlayerEvent.hh"
#include "DisconnectPlayerEvent.hh"
#include "Any.hpp"
#include "ServerRelay.hh"
#include "RoomServer.hh"

RoomServer::RoomServer(ServerRelay *server, const std::string &nameRoomServer)
  : Room(), _serverRelay(server), _nameRoomServer(nameRoomServer)
{
  std::cout << "Creating roomServer" << std::endl;
  this->_runWorldServer = new RunWorldServer(server, nameRoomServer);
  //this->_thread = Thread<RunWorldServer>();
  this->_thread.start(this->_runWorldServer, &RunWorldServer::run, Any());
}

RoomServer::~RoomServer() {
  this->_runWorldServer->isEnd(true);
  this->_thread.wait();
  delete this->_runWorldServer;
}

RunWorldServer			&RoomServer::getRunWorldServer() {return *this->_runWorldServer;}

void				RoomServer::removeRemote(Remote *remote)
{
  auto it = std::find(this->_remotes.begin(), this->_remotes.end(), remote);

  if (it == this->_remotes.end())
    return ;
  std::cout << "_______________________Disconnect player In Room________________________" << std::endl;
  this->_runWorldServer->getWorld()->sendEvent(new DisconnectPlayerEvent(remote->getPrivateHash()));
  this->_remotes.erase(it);
}

void				RoomServer::addRemote(Remote *remote)
{
  auto it = std::find(this->_remotes.begin(), this->_remotes.end(), remote);

  if (it != this->_remotes.end())
    return ;
  this->_remotes.push_back(remote);
  std::cout << "_______________________New player___________________________" << std::endl;
  this->_runWorldServer->getWorld()->sendEvent(new NewPlayerEvent(remote->getPrivateHash()));
}
