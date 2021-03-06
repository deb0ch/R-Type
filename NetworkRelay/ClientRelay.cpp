#include "ClientRelay.hh"
#include "ServerRelay.hh"
#include "TCPException.hh"
#include "UDPException.hh"
#include "LockGuard.hpp"

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

bool			ClientRelay::start()
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
	      return (true);
	    }
	  if (!buffer->end())
	    {
	      buffer->rewind();
	      auto guard = create_lock(this->_remote->getRecvBufferUDP());
	      buffer->addOffset(sizeof(unsigned int));
	      this->_remote->getRecvBufferUDP().push_back(buffer);
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
  return (false);
}

Room	*ClientRelay::getRoom(const std::string &)
{
  return (&this->_room);
}

IBuffer			*ClientRelay::getTCPBuffer()
{
  IBuffer		*buffer;

  auto guard = create_lock(this->_available_tcp);
  if (this->_available_tcp.empty())
    {
      buffer = new NetworkBuffer(4096);
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

IBuffer			*ClientRelay::getUDPBuffer()
{
  IBuffer		*buffer;

  auto guard = create_lock(this->_available_udp);
  if (this->_available_udp.empty())
    {
      buffer = new NetworkBuffer;
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

Remote			*ClientRelay::getRemote(unsigned int) const
{
  return (this->_remote);
}

Remote			*ClientRelay::getRemote(const std::string &, const int) const
{
  return (this->_remote);
}

void			ClientRelay::disposeUDPBuffer(IBuffer *buffer)
{
  auto guard = create_lock(this->_available_udp);
  this->_available_udp.push_back(buffer);
}

void			ClientRelay::disposeTCPBuffer(IBuffer *buffer)
{
  auto guard = create_lock(this->_available_tcp);
  this->_available_tcp.push_back(buffer);
}

void			ClientRelay::udpConnect()
{
  IBuffer		*buffer;

  buffer = this->getUDPBuffer();
  this->_remote->sendUDP(buffer);
}
