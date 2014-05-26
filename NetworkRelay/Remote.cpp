#include <cstring>
#include "Remote.hh"
#include "INetworkRelay.hh"
#include "Unistd.hh"
#include "TCPException.hh"
#include "LockGuard.hpp"

Remote::Remote(ISocketTCP &socket, unsigned int hash) : _temporary_tcp_buffer(4096)
{
  this->_ready = false;
  this->_tcp = &socket;
  this->_ip = "";
  this->_port = 0;
  this->_private_hash = hash;
}

Remote::~Remote()
{
  if (this->_tcp)
    this->_tcp->close();
  delete this->_tcp;
}

const ISocketTCP	&Remote::getTCPSocket() const
{
  return (*this->_tcp);
}

ISocketTCP		&Remote::getTCPSocket()
{
  return (*this->_tcp);
}

const std::string	&Remote::getIP() const
{
  return (this->_ip);
}

unsigned int		Remote::getPrivateHash() const
{
  return (this->_private_hash);
}

int			Remote::getPort() const
{
  return (this->_port);
}

void			Remote::setIP(const std::string &ip)
{
  this->_ip = ip;
}

void			Remote::setPort(const int port)
{
  this->_port = port;
}

void			Remote::setPrivateHash(const unsigned int hash)
{
  this->_private_hash = hash;
}

void			Remote::sendTCP(IBuffer *buffer)
{
  unsigned int		size;

  size = buffer->getLength();
  buffer->rewind();
  *buffer << size;
  buffer->rewind();
  auto guard = create_lock(this->_send_buffer_tcp);
  this->_send_buffer_tcp.push_back(buffer);
}

void			Remote::sendUDP(IBuffer *buffer)
{
  if (this->isReady() || buffer->getLength() == sizeof(unsigned int))
    {
      buffer->rewind();
      *buffer << this->_private_hash;
      buffer->rewind();
      auto guard = create_lock(this->_send_buffer_udp);
      this->_send_buffer_udp.push_back(buffer);
      if (this->_send_buffer_udp.size() > 1000)
	this->_send_buffer_udp.erase(this->_send_buffer_udp.begin());
    }
}

LockVector<IBuffer *>	&Remote::getRecvBufferUDP()
{
  return (this->_recv_buffer_udp);
}

LockVector<IBuffer *>	&Remote::getRecvBufferTCP()
{
  return (this->_recv_buffer_tcp);
}

const std::string	&Remote::getRoom() const
{
  return (this->_room);
}

void			Remote::setRoom(const std::string &room)
{
  this->_room = room;
}

void			Remote::networkSendTCP(INetworkRelay &network)
{
  IBuffer		*buffer;

  auto guard = create_lock(this->_send_buffer_tcp);
  if (!this->_send_buffer_tcp.empty())
    {
      buffer = this->_send_buffer_tcp.front();
      if (this->_tcp->send(*buffer))
	{
	  network.disposeTCPBuffer(buffer);
	  this->_send_buffer_tcp.erase(this->_send_buffer_tcp.begin());
	}
    }
}

bool			Remote::networkReceiveTCP(INetworkRelay &network)
{
  unsigned int		size_read;

  if (this->_recv_buffer_tcp.trylock())
    {
      auto guard = create_lock(this->_recv_buffer_tcp, true);

      this->_temporary_tcp_buffer.gotoEnd();
      try
	{
	  size_read = this->_tcp->receive(this->_temporary_tcp_buffer);
	}
      catch (const TCPException &e)
	{
	  std::cerr << e.what() << std::endl;
	  return false;
	}
      while (this->extractTCPPacket(network))
	;
      memmove(this->_temporary_tcp_buffer.getBuffer(),
	      this->_temporary_tcp_buffer.getBuffer() + this->_temporary_tcp_buffer.getPosition(),
	      this->_temporary_tcp_buffer.getRemainingLength());
      this->_temporary_tcp_buffer.setLength(this->_temporary_tcp_buffer.getRemainingLength());
      this->_temporary_tcp_buffer.rewind();
      return (size_read > 0);
    }
  return (true);
}

// Private function to get message from recv buffer
bool		Remote::extractTCPPacket(INetworkRelay &network)
{
  unsigned int	old_pos;
  unsigned int	size;
  IBuffer	*buffer;

  if (this->_temporary_tcp_buffer.getRemainingLength() >= sizeof(unsigned int))
    {
      old_pos = this->_temporary_tcp_buffer.getPosition();
      this->_temporary_tcp_buffer >> size;
      if (this->_temporary_tcp_buffer.getRemainingLength() + sizeof(size) >= size)
	{
	  buffer = network.getTCPBuffer();
	  buffer->rewind();
	  memcpy(buffer->getBuffer(),
		 this->_temporary_tcp_buffer.getBuffer() + this->_temporary_tcp_buffer.getPosition(),
		 size - sizeof(size));
	  buffer->setLength(size - sizeof(size));
	  buffer->rewind();
	  if (this->_private_hash == 0)
	    {
	      *buffer >> this->_private_hash;
	      std::cout << "Connexion established: " << this->_private_hash << std::endl;
	      network.disposeTCPBuffer(buffer);
	    }
	  else
	    {
	      buffer->addOffset(sizeof(size));
	      this->_recv_buffer_tcp.push_back(buffer);
	    }
	  this->_temporary_tcp_buffer.setPosition(this->_temporary_tcp_buffer.getPosition() +
						  size - sizeof(size));
	  return (true);
	}
      else
	this->_temporary_tcp_buffer.setPosition(old_pos);
    }
  return (false);
}

void		Remote::networkSendUDP(INetworkRelay &network, SocketUDP &udp)
{
  IBuffer	*buffer;

  auto guard = create_lock(this->_send_buffer_udp);
  if (!this->_send_buffer_udp.empty())
    {
      buffer = this->_send_buffer_udp.front();
      udp.send(*buffer,
	       this->_ip, this->_port);
      network.disposeUDPBuffer(buffer);
      this->_send_buffer_udp.erase(this->_send_buffer_udp.begin());
    }
}

bool		Remote::canSendUDP()
{
  auto guard = create_lock(this->_send_buffer_udp);
  return (!this->_send_buffer_udp.empty());
}

bool		Remote::canSendTCP()
{
  auto guard = create_lock(this->_send_buffer_tcp);
  return (!this->_send_buffer_tcp.empty());
}

void		Remote::setReady(bool ready)
{
  this->_ready = ready;
}

bool		Remote::isReady() const
{
  return (this->_ready);
}
