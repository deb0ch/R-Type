#ifdef __linux__

#include <fcntl.h>
#include "UDPException.hh"
#include "USocketUDP.hh"

static const int INVALID_SOCKET = -1;

SocketUDP::SocketUDP() {
  this->_isBlocking = true;
}

SocketUDP::SocketUDP(int socket) {
  this->_isBlocking = true;
  this->_socket = socket;
}

void SocketUDP::init() {
  int reuseAddr = 1;

  this->_socket = ::socket(AF_INET, SOCK_DGRAM, 0);
  setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr));
  if (this->_socket == INVALID_SOCKET)
    throw UDPException(errno);
}

void		SocketUDP::bind(const int port, const std::string & address) {
  struct hostent*    hostinfo = NULL;
  struct sockaddr_in sin;

  if (this->_socket == INVALID_SOCKET)
    throw UDPException(MSG_INVALID_SOCKET);
  if (address == "")
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
  else
    {
      if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
	throw UDPException("Gethostbyname has failed");
      sin.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if (::bind(this->_socket, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)))
    throw UDPException(errno);
}

int	SocketUDP::send(const IBuffer &buffer, const int address, const int port) {
  struct sockaddr_in to;

  if (this->_socket == INVALID_SOCKET)
    throw UDPException(MSG_INVALID_SOCKET);
  to.sin_addr.s_addr = htonl(address);
  to.sin_port = htons(port);
  to.sin_family = AF_INET;
  int s = ::sendto(this->_socket, buffer.getBuffer(), buffer.getLength(), MSG_NOSIGNAL,
		   reinterpret_cast<struct sockaddr*>(&to), sizeof(struct sockaddr));
  if (s == -1)
    throw UDPException(errno);
  return (s);
}

int	SocketUDP::send(const IBuffer &buffer,
			const std::string & address, const int port) {
  struct sockaddr_in	to;
  struct hostent	*hostinfo = NULL;
  int			s;

  if (this->_socket == INVALID_SOCKET)
    throw UDPException(MSG_INVALID_SOCKET);
  if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
    throw UDPException("Gethostbyname as failed");
  to.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
  to.sin_port = htons(port);
  to.sin_family = AF_INET;

  s = ::sendto(this->_socket, buffer.getBuffer(), buffer.getLength(), MSG_NOSIGNAL,
	       reinterpret_cast<struct sockaddr*>(&to), sizeof(struct sockaddr));
  if (s == -1)
    throw UDPException(errno);
  return (s);
}

int	SocketUDP::receive(IBuffer &buffer, std::string &address, int &port) {
  struct sockaddr_in	from;
  socklen_t		lenfrom = sizeof(from);

  if (this->_socket == INVALID_SOCKET)
    throw UDPException(MSG_INVALID_SOCKET);
  int s = ::recvfrom(this->_socket, buffer.getBuffer(), buffer.getMaxSize(), 0,
		     reinterpret_cast<struct sockaddr*>(&from), &lenfrom);
  if (s == -1)
    throw UDPException(errno);
  buffer.setLength(s);
  buffer.rewind();
  address = ::inet_ntoa(from.sin_addr);
  port = ::ntohs(from.sin_port);
  return (s);
}

void SocketUDP::setBlocking(bool const blocking) {
  int status;
  if (this->_socket == INVALID_SOCKET)
    throw UDPException(MSG_INVALID_SOCKET);

  status = ::fcntl(this->_socket, F_GETFL);
  if (blocking)
    ::fcntl(this->_socket, F_SETFL, status & ~O_NONBLOCK);
  else
    ::fcntl(this->_socket, F_SETFL, status | O_NONBLOCK);
  this->_isBlocking = blocking;
}

bool SocketUDP::isBlocking() const {
  return (this->_isBlocking);
}

int		SocketUDP::getHandle() const {
  return (this->_socket);
}

void SocketUDP::close() {
  ::close(this->_socket);
}

SocketUDP::~SocketUDP() {
  this->close();
}

#endif
