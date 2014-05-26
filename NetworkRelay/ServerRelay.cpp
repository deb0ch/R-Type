#include <ctime>
#include "ServerRelay.hh"
#include "NetworkBuffer.hh"
#include "Unistd.hh"
#include "NewPlayerEvent.hh"
#include "DisconnectPlayerEvent.hh"
#include "LockGuard.hpp"

ServerRelay::ServerRelay(World *world, int port, int nb_pending_connection)
  : _network_initializer(), _world(world)
{
  srand(static_cast<unsigned int>(time(NULL)));
  this->_server_socket_tcp.init();
  this->_server_socket_udp.init();
  this->_server_socket_tcp.bind(port);
  this->_server_socket_tcp.listen(nb_pending_connection);
  this->_server_socket_udp.bind(port);
  this->_select.initReads();
  this->_select.initWrites();
}

ServerRelay::~ServerRelay()
{
  this->_server_socket_udp.close();
  this->_server_socket_tcp.close();
}

void	ServerRelay::waitForEvent()
{
  this->_select.reset();
  this->_select.addRead(this->_server_socket_tcp.getHandle());
  this->_select.addRead(this->_server_socket_udp.getHandle());
  std::for_each(this->_remotes.begin(), this->_remotes.end(),
		[this] (std::pair<const std::string, Room> &pair) -> void
		{
		  std::vector<Remote *> &remotes = pair.second.getRemotes();
		  std::for_each(remotes.begin(), remotes.end(),
				[this] (Remote *remote) -> void
				{
				  this->_select.addRead(remote->getTCPSocket().getHandle());

				  if (remote->canSendUDP())
				    {
				      this->_select.addWrite(this->_server_socket_udp.getHandle());
				    }
				  if (remote->canSendTCP())
				    {
				      this->_select.addWrite(remote->getTCPSocket().getHandle());
				    }
				});
		});
  this->_select.setTimeOut(0, 10000);
  this->_select.doSelect();
}

void	ServerRelay::start(Any)
{
  this->start();
}

void	ServerRelay::start()
{
  while (1)
    {
      this->waitForEvent();

      if (this->_select.issetReads(this->_server_socket_udp.getHandle()))
	this->receiveUDP();

      if (this->_select.issetReads(this->_server_socket_tcp.getHandle()))
	this->addClient();

      this->manageRemotes();
    }
}

void		ServerRelay::manageRemotes()
{
  auto it = this->_remotes.begin();
  Room		*room;

  while (it != this->_remotes.end())
    {
      room = &it->second;
      std::vector<Remote *> &remotes = room->getRemotes();
      std::for_each(remotes.begin(), remotes.end(),
		    [this, &room] (Remote *remote) -> void
		    {
		      if (this->_select.issetWrites(remote->getTCPSocket().getHandle()))
			remote->networkSendTCP(*this);

		      if (this->_select.issetWrites(this->_server_socket_udp.getHandle()))
			{
			  remote->networkSendUDP(*this, this->_server_socket_udp);
			  // this->_select.removeWrite(this->_server_socket_udp);
			}

		      if (this->_select.issetReads(remote->getTCPSocket().getHandle()))
			{
			  if (!remote->networkReceiveTCP(*this))
			    room->disconnectRemote(remote);
			}
		    });
      if (room->trylock())
	{
	  auto guard_room = create_lock(*room, true);

	  std::vector<Remote *> &remotes_disconnect = room->getPendingDisonnectRemotes();
	  std::for_each(remotes_disconnect.begin(), remotes_disconnect.end(),
			[&room, this] (Remote *remote) -> void
			{
			  this->removeRemote(remote);
			  room->removeRemote(remote);
			});
	  remotes_disconnect.clear();
	  if (room->getRemotes().empty())
	    {
	      if (this->_mutex_room.trylock())
		{
		  auto guard = create_lock(this->_mutex_room, true);

		  guard_room.setUnLocked();
		  it = this->_remotes.erase(it);
		  room = NULL;
		  std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!ERASE ROOM!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		}
	    }
	}
      if (room)
	++it;
    }
}

void		ServerRelay::removeRemote(Remote *remote)
{
  this->_select.removeRead(remote->getTCPSocket().getHandle());
  this->_select.removeWrite(remote->getTCPSocket().getHandle());
  this->_world->sendEvent(new DisconnectPlayerEvent(remote->getPrivateHash()));
}

/**
 * @todo Add more verifications than only id (like Port and IP) to know which client is talking
 */
void		ServerRelay::receiveUDP()
{
  IBuffer	*buffer = this->getUDPBuffer();
  std::string	ip;
  int		port;
  unsigned int	id;
  Remote	*remote;

  this->_server_socket_udp.receive(*buffer, ip, port);
  buffer->rewind();
  *buffer >> id;
  remote = this->getRemote(id);
  if (remote)
    {
      remote->setIP(ip);
      remote->setPort(port);
      remote->setReady(true);
      if (buffer->end())
	{
	  this->udpConnect(remote);
	  this->_world->sendEvent(new NewPlayerEvent(remote->getPrivateHash()));
	}
      else
	{
	  auto guard = create_lock(remote->getRecvBufferUDP());
	  buffer->addOffset(sizeof(unsigned int));
	  remote->getRecvBufferUDP().push_back(buffer);
	}
    }
  else
    std::cout << "Remote not found" << std::endl;
}

void		ServerRelay::addClient()
{
  ISocketTCP	*new_client;
  Remote	*remote;
  IBuffer	*buffer;
  unsigned int	hash;

  std::cout << "Adding client" << std::endl;
  new_client = this->_server_socket_tcp.accept();
  hash = this->generateHash();
  std::cout << "GENERATING HASH: " << hash << std::endl;
  remote = new Remote(*new_client, hash);
  this->_remotes["default"].getRemotes().push_back(remote);
  buffer = this->getTCPBuffer();
  *buffer << hash;
  remote->sendTCP(buffer);
}

unsigned int	ServerRelay::generateHash()
{
  unsigned int	hash;

  do
    {
      hash = rand();
    } while (this->getRemote(hash) != NULL || hash == 0);
  return (hash);
}

Remote		*ServerRelay::getRemote(unsigned int hash)
{
  for(auto it = this->_remotes.begin(); it != this->_remotes.end(); ++it)
    {
      std::vector<Remote *> &remotes = it->second.getRemotes();
      auto result = std::find_if(remotes.begin(), remotes.end(),
				 [this, &hash] (Remote *remote) -> bool
				 {
				   if (remote->getPrivateHash() == hash)
				     return true;
				   return false;
				 });
      if (result != remotes.end())
	return (*result);
    }
  return (NULL);
}

Remote		*ServerRelay::getRemote(const std::string &ip, const int port)
{
  for(auto it = this->_remotes.begin(); it != this->_remotes.end(); ++it)
    {
      std::vector<Remote *> &remotes = it->second.getRemotes();
      auto result = std::find_if(remotes.begin(), remotes.end(),
				 [this, &ip, &port] (Remote *remote) -> bool
				 {
				   if (remote->getIP() == ip && remote->getPort() == port)
				     return true;
				   return false;
				 });
      if (result != remotes.end())
	return (*result);
    }
  return (NULL);
}

IBuffer			*ServerRelay::getTCPBuffer()
{
  IBuffer		*buffer;

  auto guard = create_lock(this->_available_tcp);
  if (this->_available_tcp.empty())
    {
      buffer = new NetworkBuffer(4096);
      std::cout << "creating buffer tcp: " << buffer << std::endl;
    }
  else
    {
      buffer = this->_available_tcp.front();
      this->_available_tcp.erase(this->_available_tcp.begin());
      buffer->reset();
    }
  buffer->setPosition(sizeof(unsigned int));
  return (buffer);
}

IBuffer			*ServerRelay::getUDPBuffer()
{
  IBuffer		*buffer;

  auto guard = create_lock(this->_available_udp);
  if (this->_available_udp.empty())
    {
      buffer = new NetworkBuffer;
      std::cout << "creating buffer udp: " << buffer << std::endl;
    }
  else
    {
      buffer = this->_available_udp.front();
      this->_available_udp.erase(this->_available_udp.begin());
      buffer->reset();
    }
  buffer->setPosition(sizeof(unsigned int));
  return (buffer);
}

void			ServerRelay::disposeUDPBuffer(IBuffer *buffer)
{
  auto guard = create_lock(this->_available_udp);
  this->_available_udp.push_back(buffer);
}

void			ServerRelay::disposeTCPBuffer(IBuffer *buffer)
{
  auto guard = create_lock(this->_available_tcp);
  this->_available_tcp.push_back(buffer);
}

Room			*ServerRelay::getRoom(const std::string &room_name)
{
  auto guard = create_lock(this->_mutex_room);
  auto it = this->_remotes.find(room_name);

  if (it == this->_remotes.end())
    return (NULL);
  return &(it->second);
}

void				ServerRelay::udpConnect(Remote *remote)
{
  IBuffer			*buffer;

  buffer = this->getUDPBuffer();
  remote->sendUDP(buffer);
}
