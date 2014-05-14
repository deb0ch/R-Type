#include "ClientRelay.hh"
#include "TCPException.hh"
#include "UDPException.hh"

ClientRelay::ClientRelay(const std::string &addr, int port) : _network_initializer()
{
  SocketTCP	*sock = new SocketTCP;

  sock->init();
  sock->connect(addr, port);
  this->_remote = new Remote(*sock);
  this->_socket_udp.init();
  this->_socket_udp.bind(port);
  this->_select.initReads();
  this->_select.initWrites();
  this->_select.addRead(this->_remote->getTCPSocket().getHandle());
  this->_select.addRead(this->_socket_udp.getHandle());
}

ClientRelay::~ClientRelay()
{
  this->_socket_udp.close();
  this->_socket_tcp.close();
  delete this->_remote;
}

void			ClientRelay::waitForEvent()
{
  this->_select.resetWrites();
  if (!this->_remote.getSendBufferTCP().isEmpty())
    this->_select.addWrite(this->_remote.getTCPSocket().getHandle());
  if (!this->_remote.getSendBufferUDP().isEmpty())
    this->_select.addRead(this->_socket_udp.getHandle());
  this->_select.doSelect();
}

void			ClientRelay::start()
{
  while (1)
    {
      this->waitForEvent();

      if (this->_select.issetReads(this->_socket_udp.getHandle()))
	{
	  IBuffer *buffer = this->getUDPBuffer();
	  std::string ip;
	  int port;
	  this->_server_socket_udp.receive(*buffer, ip, port);
	  Remote *remote = this->getRemote(ip, port);
	  if (remote)
	    remote->getRecvBufferUDP().push_back(buffer);
	}

      if (this->_select.issetReads(this->_remote->getTCPSocket().getHandle()))
	this->_remote->networkReceiveTCP(*this);

      if (this->_select.issetWrites(this->_remote->getTCPSocket().getHandle()))
	this->_remote->networkSendTCP();

      if (this->_select.issetWrites(this->_socket_udp.getHandle()))
	this->_remote->networkSendUDP(this->_socket_udp);
    }
}

std::vector<Remote *>	ClientRelay::getRemotes(const std::string &room_name)
{
  std::vector<Remote *>	remotes;

  this->_remote->lock();
  remotes.push_back(this->_remote);
  return (remotes);
}

void			ClientRelay::sendBroadcastUDP(const std::string &, IBuffer &buffer)
{
  this->_remote->sendUDP(buffer);
}

void			ClientRelay::sendBroadcastTCP(const std::string &, IBuffer &buffer)
{
  this->_remote->sendTCP(buffer);
}

IBuffer			*ClientRelay::getTCPBuffer()
{
  return (new NetworkBuffer(4096));
}

IBuffer			*ClientRelay::getUDPBuffer()
{
  IBuffer		*buffer;

  buffer = new NetworkBuffer;
  buffer->setPosition(sizeof(unsigned int));
  return (buffer);
}

Remote			*ClientRelay::getRemote(unsigned int)
{
  return (this->_remote);
}

Remote			*ClientRelay::getRemote(const std::string &ip, const int port)
{
  return (this->_remote);
}

void			ClientRelay::disposeUDPBuffer(IBuffer *buffer)
{
  delete buffer;
}

void			ClientRelay::disposeTCPBuffer(IBuffer *buffer)
{
  delete buffer;
}
