#include "ClientRelay.hh"
#include "TCPException.hh"
#include "UDPException.hh"

ClientRelay::ClientRelay(const std::string &addr, int port) : _network_initializer(), _select()
{
  SocketTCP	*sock = new SocketTCP;

  sock->init();
  this->_socket_udp.init();
  sock->connect(addr, port);
  this->_remote = new Remote(*sock);
  this->_remote->setIP(addr);
  this->_remote->setPort(port);
  this->_room.getRemotes().push_back(this->_remote);
  this->_select.initReads();
  this->_select.initWrites();
  this->_select.addRead(this->_remote->getTCPSocket().getHandle());
  this->_select.addRead(this->_socket_udp.getHandle());
}

ClientRelay::~ClientRelay()
{
  this->_socket_udp.close();
}

void			ClientRelay::waitForEvent()
{
  this->_select.reset();
  this->_select.addRead(this->_remote->getTCPSocket().getHandle());
  this->_select.addRead(this->_socket_udp.getHandle());
  if (this->_remote->canSendTCP())
    {
      this->_select.addWrite(this->_remote->getTCPSocket().getHandle());
    }
  if (this->_remote->canSendUDP() || (!this->_remote->isReady() && this->_remote->getPrivateHash() != 0))
    {
      this->_select.addWrite(this->_socket_udp.getHandle());
    }
  this->_select.setTimeOut(0, 10000);
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
	    {
	      buffer->rewind();
	      this->_remote->getRecvBufferUDP().lock();
	      buffer->addOffset(sizeof(unsigned int));
	      this->_remote->getRecvBufferUDP().push_back(buffer);
	      this->_remote->getRecvBufferUDP().unlock();
	    }
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
  std::cout << "DISCONNECTED :O" << std::endl;
}

Room	*ClientRelay::getRoom(const std::string &)
{
  this->_room.lock();
  return (&this->_room);
}

IBuffer			*ClientRelay::getTCPBuffer()
{
  IBuffer		*buffer;

  if (this->_available_tcp.isEmpty())
    {
      buffer = new NetworkBuffer(4096);
      std::cout << "creating buffer tcp: " << buffer << std::endl;
    }
  else
    {
      buffer = this->_available_tcp.getNextPop();
      buffer->reset();
    }
  buffer->setPosition(sizeof(unsigned int));
  return (buffer);
}

IBuffer			*ClientRelay::getUDPBuffer()
{
  IBuffer		*buffer;

  if (this->_available_udp.isEmpty() || 1)
    {
      buffer = new NetworkBuffer;
      // std::cout << "creating buffer udp: " << buffer << std::endl;
    }
  else
    {
      buffer = this->_available_udp.getNextPop();
      buffer->reset();
    }
  buffer->setPosition(sizeof(unsigned int));
  return (buffer);
}

Remote			*ClientRelay::getRemote(unsigned int)
{
  return (this->_remote);
}

Remote			*ClientRelay::getRemote(const std::string &, const int)
{
  return (this->_remote);
}

void			ClientRelay::disposeUDPBuffer(IBuffer *buffer)
{
  this->_available_udp.push(buffer);
}

void			ClientRelay::disposeTCPBuffer(IBuffer *buffer)
{
  this->_available_tcp.push(buffer);
}

void			ClientRelay::udpConnect()
{
  IBuffer		*buffer;

  buffer = this->getUDPBuffer();
  this->_remote->sendUDP(buffer);
}
