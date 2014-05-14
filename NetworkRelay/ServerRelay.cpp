#include <ctime>
#include "ServerRelay.hh"
#include "NetworkBuffer.hh"

ServerRelay::ServerRelay(int port, int nb_pending_connection) : _network_initializer()
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
  std::for_each(this->_remotes.begin(), this->_remotes.end(),
		[] (Remote *remote) -> void {
		  delete remote;
		});
}

void	ServerRelay::waitForEvent()
{
  this->_select.reset();
  this->_select.addRead(this->_server_socket_tcp.getHandle());
  this->_select.addRead(this->_server_socket_udp.getHandle());
  std::for_each(this->_remotes.begin(), this->_remotes.end(),
		[this] (Remote *remote) -> void {

		  this->_select.addRead(remote->getTCPSocket().getHandle());

		  if (!remote->getSendBufferUDP().isEmpty())
		    {
		      std::cout << "Add write UDP: " << this->_server_socket_udp.getHandle() << std::endl;
		      this->_select.addWrite(this->_server_socket_udp.getHandle());
		    }
		  if (!remote->getSendBufferTCP().isEmpty())
		    {
		      std::cout << "Add write TCP" << remote->getTCPSocket().getHandle() << std::endl;
		      this->_select.addWrite(remote->getTCPSocket().getHandle());
		    }

		});
  std::cout << "Waiting.." << std::endl;
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
      std::cout << "Something happens" << std::endl;

      this->manageRemotes();

      if (this->_select.issetReads(this->_server_socket_udp.getHandle()))
	this->receiveUDP();

      if (this->_select.issetReads(this->_server_socket_tcp.getHandle()))
	this->addClient();
    }
}

void		ServerRelay::manageRemotes()
{
  auto		it = this->_remotes.begin();

  while (it != this->_remotes.end())
    {
      if (this->_select.issetWrites((*it)->getTCPSocket().getHandle()))
	(*it)->networkSendTCP(*this);

      if (this->_select.issetWrites(this->_server_socket_udp.getHandle()))
	(*it)->networkSendUDP(*this, this->_server_socket_udp);

      if (this->_select.issetReads((*it)->getTCPSocket().getHandle()))
	{
	  if (!(*it)->networkReceiveTCP(*this))
	    {
	      this->removeRemote(*it);
	      it = this->_remotes.erase(it);
	    }
	  else
	    ++it;
	}
      else
	++it;
    }
}

void		ServerRelay::removeRemote(Remote *remote)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  this->_select.removeRead(remote->getTCPSocket().getHandle());
  this->_select.removeWrite(remote->getTCPSocket().getHandle());
  delete remote;
}

/**
 * @todo Add more verifications than only id (like Port and IP) to know which client is talking
 */
void		ServerRelay::receiveUDP()
{
  IBuffer *buffer = this->getUDPBuffer();
  std::string ip;
  int port;
  unsigned int id;
  Remote *remote;

  std::cout << "Receiving UDP" << std::endl;
  this->_server_socket_udp.receive(*buffer, ip, port);
  *buffer >> id;
  remote = this->getRemote(id);
  if (remote)
    remote->getRecvBufferUDP().push(buffer);
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
  remote = new Remote(*new_client, hash);
  remote->setRoom("default");
  this->_remotes.push_back(remote);
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
  auto it = std::find_if(this->_remotes.begin(), this->_remotes.end(), [hash] (Remote *remote) -> bool {
      if (remote->getPrivateHash() == hash)
	return (true);
      return (false);
    });

  if (it == this->_remotes.end())
    return (NULL);
  return (*it);
}

Remote		*ServerRelay::getRemote(const std::string &ip, const int port)
{
  auto it = std::find_if(this->_remotes.begin(), this->_remotes.end(), [&ip, port] (Remote *remote) -> bool {
      if (remote->getIP() == ip && remote->getPort() == port)
	return (true);
      return (false);
    });

  if (it == this->_remotes.end())
    return (NULL);
  return (*it);
}

IBuffer			*ServerRelay::getTCPBuffer()
{
  IBuffer *buffer;

  buffer = new NetworkBuffer(4096);
  buffer->setPosition(sizeof(unsigned int));
  std::cout << "creating: " << buffer << std::endl;
  return (buffer);
}

IBuffer			*ServerRelay::getUDPBuffer()
{
  IBuffer *buffer;

  buffer = new NetworkBuffer;
  buffer->setPosition(sizeof(unsigned int));
  std::cout << "creating: " << buffer << std::endl;
  return (buffer);
}

void			ServerRelay::disposeUDPBuffer(IBuffer *buffer)
{
  delete buffer;
}

void			ServerRelay::disposeTCPBuffer(IBuffer *buffer)
{
  delete buffer;
}

std::vector<Remote *>		ServerRelay::getRemotes(const std::string &room_name)
{
  std::vector<Remote *>		ret;

  std::for_each(this->_remotes.begin(), this->_remotes.end(), [&ret, &room_name] (Remote *remote) -> void {
      if (remote->getRoom() == room_name)
	{
	  remote->lock();
	  ret.push_back(remote);
	}
    });
  return (ret);
}

void				ServerRelay::sendBroadcastUDP(const std::string &room_name, IBuffer &buffer)
{
  std::for_each(this->_remotes.begin(), this->_remotes.end(), [this, &room_name, &buffer] (Remote *remote) -> void {
      if (remote->getRoom() == room_name)
	{
	  IBuffer *cpy = this->getUDPBuffer();
	  *cpy = buffer;
	  remote->sendUDP(cpy);
	}
    });
}

void				ServerRelay::sendBroadcastTCP(const std::string &room_name, IBuffer &buffer)
{
  std::for_each(this->_remotes.begin(), this->_remotes.end(), [this, &room_name, &buffer] (Remote *remote) -> void {
      if (remote->getRoom() == room_name)
	{
	  IBuffer *cpy = this->getTCPBuffer();
	  *cpy = buffer;
	  remote->sendTCP(cpy);
	}
    });
}

bool				ServerRelay::isReady() const
{
  return (true);
}
