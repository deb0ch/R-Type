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
  if (!this->_remote.getSendBufferTCP().empty())
    this->_select.addWrite(this->_remote.getTCPSocket().getHandle());
  if (!this->_remote.getSendBufferUDP().empty())
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
    }
}

std::vector<Remote *>	ClientRelay::getRemotes(const std::string &room_name)
{
}

void			ClientRelay::sendBroadcastUDP(const std::string &room_name, IBuffer &buffer)
{
}

void			ClientRelay::sendBroadcastTCP(const std::string &room_name, IBuffer &buffer)
{
}

IBuffer 		*ClientRelay::getTCPBuffer()
{
}

IBuffer 		*ClientRelay::getUDPBuffer()
{
}

void			ClientRelay::clearRecvBufferUDP(Remote &)
{
}

void			ClientRelay::clearRecvBufferTCP(Remote &)
{
}

Remote			*ClientRelay::getRemote(unsigned int)
{
}

Remote			*ClientRelay::getRemote(const std::string &ip, const int port)
{
}

void			ClientRelay::disposeUDPBuffer(IBuffer *)
{
}

void			ClientRelay::disposeTCPBuffer(IBuffer *)
{
}
