#include "ClientRelay.hh"
#include "TCPException.hh"
#include "UDPException.hh"

ClientRelay::ClientRelay(const std::string &addr, int port) : _network_initializer(), _select(0, 1000)
{
  SocketTCP	*sock = new SocketTCP;

  sock->init();
  sock->connect(addr, port);
  this->_remote = new Remote(*sock);
  this->_remote->setIP(addr);
  this->_remote->setPort(port);
  this->_socket_udp.init();
  this->_select.initReads();
  this->_select.initWrites();
  this->_select.addRead(this->_remote->getTCPSocket().getHandle());
  this->_select.addRead(this->_socket_udp.getHandle());
}

ClientRelay::~ClientRelay()
{
  this->_socket_udp.close();
  delete this->_remote;
}

void			ClientRelay::waitForEvent()
{
  this->_select.reset();
  this->_select.addRead(this->_remote->getTCPSocket().getHandle());
  this->_select.addRead(this->_socket_udp.getHandle());
  if (this->_remote->canSendTCP())
    {
      std::cout << "Add write TCP" << std::endl;
      this->_select.addWrite(this->_remote->getTCPSocket().getHandle());
    }
  if (this->_remote->canSendUDP() || (!this->_remote->isReady() && this->_remote->getPrivateHash() != 0))
    {
      std::cout << "Add write UDP" << std::endl;
      this->_select.addWrite(this->_socket_udp.getHandle());
    }
  this->_select.doSelect();
}

void			ClientRelay::start(Any)
{
  this->start();
}

void			ClientRelay::start()
{
  bool			disconnect;

  disconnect = false;
  while (!disconnect)
    {
      this->waitForEvent();
      if (this->_select.issetReads(this->_socket_udp.getHandle()))
	{
	  IBuffer	*buffer = this->getUDPBuffer();
	  std::string	ip;
	  int		port;

	  this->_socket_udp.receive(*buffer, ip, port);
	  buffer->setPosition(sizeof(unsigned int));
	  if (!this->_remote->isReady())
	    {
	      this->_remote->setReady(true);
	      std::cout << "CLIENT READY" << std::endl;
	    }
	  if (!buffer->end())
	    this->_remote->getRecvBufferUDP().push(buffer);
	}

      if (this->_select.issetWrites(this->_socket_udp.getHandle()))
	{
	  if (!this->_remote->isReady() && this->_remote->getPrivateHash() != 0)
	    this->udpConnect();
	  this->_remote->networkSendUDP(*this, this->_socket_udp);
	}

      if (this->_select.issetWrites(this->_remote->getTCPSocket().getHandle()))
	this->_remote->networkSendTCP(*this);

      if (this->_select.issetReads(this->_remote->getTCPSocket().getHandle()))
	{
	  if (!this->_remote->networkReceiveTCP(*this))
	    disconnect = true;
	}
    }
}

std::vector<Remote *>	ClientRelay::getRemotes(const std::string &room_name)
{
  std::vector<Remote *>	remotes;

  if (this->_remote->trylock())
    {
      if (this->_remote->isReady())
	{
	  remotes.push_back(this->_remote);
	}
      else
	this->_remote->unlock();
    }
  return (remotes);
}

void			ClientRelay::sendBroadcastUDP(const std::string &, IBuffer &buffer)
{
  this->_remote->sendUDP(&buffer);
}

void			ClientRelay::sendBroadcastTCP(const std::string &, IBuffer &buffer)
{
  this->_remote->sendTCP(&buffer);
}

IBuffer			*ClientRelay::getTCPBuffer()
{
  IBuffer		*buffer;

  buffer = new NetworkBuffer(4096);
  buffer->setPosition(sizeof(unsigned int));
  std::cout << "creating buffer: " << buffer << std::endl;
  return (buffer);
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

void			ClientRelay::udpConnect()
{
  IBuffer		*buffer;

  buffer = this->getUDPBuffer();
  this->_remote->sendUDP(buffer);
}
