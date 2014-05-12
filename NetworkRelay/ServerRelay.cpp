#include <ctime>
#include "ServerRelay.hh"
#include "NetworkBuffer.hh"

ServerRelay::ServerRelay(int port, int nb_pending_connection)
{
  srand(time(NULL));
  this->_server_socket_tcp.bind(port);
  this->_server_socket_tcp.listen(nb_pending_connection);
  this->_server_socket_udp.bind(port);
  this->_select.initReads();
  this->_select.initWrites();
  this->_select.addRead(this->_server_socket_tcp.getHandle());
  this->_select.addRead(this->_server_socket_udp.getHandle());
}

ServerRelay::~ServerRelay()
{
  this->_server_socket_udp.close();
  this->_server_socket_tcp.close();
  std::for_each(this->_remotes.begin(), this->_remotes.end(),
		[] (Remote *remote) -> void {
		  remote->getTCPSocket().close();
		  delete remote;
		});
}

void	ServerRelay::waitForEvent()
{
  this->_select.resetWrites();
  std::for_each(this->_remotes.begin(), this->_remotes.end(),
		[this] (Remote *remote) -> void {
		  if (!remote->getSendBufferUDP().empty())
		    this->_select.addWrite(this->_server_socket_udp.getHandle());
		  if (!remote->getSendBufferTCP().empty())
		    this->_select.addWrite(remote->getTCPSocket().getHandle());
		});
  this->_select.doSelect();
}

void	ServerRelay::start()
{
  while (1)
    {
      this->waitForEvent();
      if (this->_select.issetReads(this->_server_socket_tcp.getHandle()))
	this->addClient();
      std::for_each(this->_remotes.begin(), this->_remotes.end(), [this] (Remote *remote) -> void {

	  if (this->_select.issetReads(remote->getTCPSocket().getHandle()))
	    remote->networkReceiveTCP(*this);

	  if (this->_select.issetWrites(remote->getTCPSocket().getHandle()))
	    remote->networkSendTCP();

	  if (this->_select.issetWrites(this->_server_socket_udp.getHandle()))
	    remote->networkSendUDP(this->_server_socket_udp);
	});
      if (this->_select.issetReads(this->_server_socket_udp.getHandle()))
	{
	  IBuffer *buffer = this->getUDPBuffer();
	  std::string ip;
	  int port;
	  this->_server_socket_udp.receive(*buffer, ip, port);
	  Remote *remote = this->getRemote(ip, port);
	  if (remote)
	    remote->getRecvBufferUDP().push_back(buffer);
	}
    }
}

void		ServerRelay::addClient()
{
  ISocketTCP	*new_client;
  Remote	*remote;
  IBuffer	*buffer;
  unsigned int	hash;

  new_client = this->_server_socket_tcp.accept();
  hash = this->generateHash();
  remote = new Remote(*new_client, hash);
  remote->setRoom("default");
  this->_remotes.push_back(remote);
  this->_select.addRead(new_client->getHandle());
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
    } while (this->getRemote(hash) != NULL);
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
  return (new NetworkBuffer(4096));
}

IBuffer			*ServerRelay::getUDPBuffer()
{
  IBuffer *buffer;

  buffer = new NetworkBuffer;
  buffer->setPosition(sizeof(unsigned int));
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
	ret.push_back(remote);
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
