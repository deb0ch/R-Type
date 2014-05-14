#include <cstring>
#include "Remote.hh"
#include "INetworkRelay.hh"

Remote::Remote(ISocketTCP &socket, unsigned int hash)
{
  this->_tcp = &socket;
  this->_ip = "";
  this->_port = 0;
  this->_private_hash = hash;
}

Remote::~Remote()
{
  this->_mutex.lock();
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

SafeFifo<IBuffer *>	&Remote::getSendBufferUDP()
{
  return (this->_send_buffer_udp);
}

SafeFifo<IBuffer *>	&Remote::getSendBufferTCP()
{
  return (this->_send_buffer_tcp);
}

void			Remote::sendTCP(IBuffer *buffer)
{
  unsigned int		size;

  size = buffer->getLength();
  buffer->rewind();
  *buffer << size;
  buffer->rewind();
  this->_send_buffer_tcp.push(buffer);
}

void			Remote::sendUDP(IBuffer *buffer)
{
  buffer->rewind();
  *buffer << this->_private_hash;
  buffer->rewind();
  this->_send_buffer_udp.push(buffer);
}

SafeFifo<IBuffer *>	&Remote::getRecvBufferUDP()
{
  return (this->_recv_buffer_udp);
}

SafeFifo<IBuffer *>	&Remote::getRecvBufferTCP()
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

  if (this->_send_buffer_tcp.isEmpty())
    return ;
  buffer = this->_send_buffer_tcp.getNext();
  if (this->_tcp->send(*buffer))
    network.disposeTCPBuffer(buffer);
}

# include <stdexcept>

void			Remote::networkReceiveTCP(INetworkRelay &network)
{
  unsigned int		size;
  IBuffer		*buffer;

  this->_tcp->receive(this->_temporary_tcp_buffer);
  if (this->_temporary_tcp_buffer.getLength() >= sizeof(unsigned int))
    {
      this->_temporary_tcp_buffer.rewind();
      this->_temporary_tcp_buffer >> size;
      if (size >= this->_temporary_tcp_buffer.getLength())
	{
	  /**
	   * @todo copy the surplus of data we read into the begining of this->_temporary_tcp_buffer,
	   * add set its position to the end of the message
	   */
	  if (size > this->_temporary_tcp_buffer.getLength())
	    throw std::logic_error("NOT IMPLEMENTED");
	  buffer = network.getTCPBuffer();
	  buffer->rewind();
	  memcpy(buffer->getBuffer(),
		 this->_temporary_tcp_buffer.getBuffer() + sizeof(unsigned int),
		 size - sizeof(unsigned int)); // Change this
	  buffer->setLength(size - sizeof(unsigned int));
	  buffer->rewind();
	  if (this->_private_hash == 0)
	    {
	      *buffer >> this->_private_hash;
	      network.disposeTCPBuffer(buffer);
	    }
	  else
	    this->_recv_buffer_tcp.push(buffer);
	}
      this->_temporary_tcp_buffer.rewind();
    }
}

void		Remote::networkSendUDP(INetworkRelay &network, SocketUDP &udp)
{
  IBuffer	*buffer;

  if (this->_send_buffer_udp.isEmpty())
    return ;
  buffer = this->_send_buffer_udp.getNext();
  udp.send(*buffer,
	   this->_ip, this->_port);
  network.disposeUDPBuffer(buffer);
}

void		Remote::lock()
{
  this->_mutex.lock();
}

void		Remote::unlock()
{
  this->_mutex.unlock();
}

bool		Remote::isUnLocked()
{
  return (this->_mutex.status() == IMutex::UNLOCKED);
}
