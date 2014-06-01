#include <algorithm>
#include "NewPlayerEvent.hh"
#include "DisconnectPlayerEvent.hh"
#include "Any.hpp"
#include "ServerRelay.hh"
#include "RoomServer.hh"

RoomServer::RoomServer(ServerRelay *server, const std::string &nameRoomServer)
  : Room(), _serverRelay(server), _nameRoomServer(nameRoomServer)
{
  std::cout << "Creating new room: " << this->_nameRoomServer << std::endl;
  this->_runWorldServer = new RunWorldServer(server, nameRoomServer);
  this->_thread.start(this->_runWorldServer, &RunWorldServer::run);
}

RoomServer::~RoomServer() {
  this->_runWorldServer->isEnd(true);
  this->_thread.wait();
  delete this->_runWorldServer;
  std::cout << "Room deletion completed" << std::endl;
}

RunWorldServer			&RoomServer::getRunWorldServer() {return *this->_runWorldServer;}

const RunWorldServer		&RoomServer::getRunWorldServer() const
{
  return *this->_runWorldServer;
}

void				RoomServer::removeRemote(Remote *remote)
{
  auto it = std::find(this->_remotes.begin(), this->_remotes.end(), remote);

  if (it == this->_remotes.end())
    return ;
  std::cout << "Remove player from the room: " << this->_nameRoomServer << std::endl;
  this->_runWorldServer->getWorld()->sendEvent(new DisconnectPlayerEvent(remote->getPrivateHash()));
  this->_remotes.erase(it);
}

void				RoomServer::addRemote(Remote *remote)
{
  auto it = std::find(this->_remotes.begin(), this->_remotes.end(), remote);

  if (it != this->_remotes.end())
    return ;
  this->_remotes.push_back(remote);
  std::cout << "New player came in room: " << this->_nameRoomServer << std::endl;
  this->_runWorldServer->getWorld()->sendEvent(new NewPlayerEvent(remote->getPrivateHash()));
}
