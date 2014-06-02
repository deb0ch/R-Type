#ifdef __linux__

#include <fcntl.h>
#include "TCPException.hh"
#include "USocketTCP.hh"

static const int INVALID_SOCKET = -1;

SocketTCP::SocketTCP() {
  this->_isBlocking = true;
}

SocketTCP::SocketTCP(int socket) {
  this->_isBlocking = true;
  this->_socket = socket;
}

void SocketTCP::init() {
  int reuseAddr = 1;

  this->_socket = ::socket(AF_INET, SOCK_STREAM, 0);
  if (this->_socket == INVALID_SOCKET)
    throw TCPException(errno);
  setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr));
}

int		SocketTCP::getHandle() const {
  return (this->_socket);
}

void SocketTCP::setBlocking(bool const blocking) {
  int status;

  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  status = ::fcntl(this->_socket, F_GETFL);
  if (blocking)
    ::fcntl(this->_socket, F_SETFL, status & ~O_NONBLOCK);
  else
    ::fcntl(this->_socket, F_SETFL, status | O_NONBLOCK);
  this->_isBlocking = blocking;
}

bool SocketTCP::isBlocking() const {
  return (this->_isBlocking);
}

void		SocketTCP::listen(const std::size_t block)
{
  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  if (::listen(this->_socket, block) < 0)
    throw TCPException(errno);
}

void		SocketTCP::bind(int port, const std::string & address) {
  struct hostent*    hostinfo = NULL;
  struct sockaddr_in sin;

  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  if (address == "")
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
  else
    {
      if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
	throw TCPException("Gethostbyname has failed");
      sin.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if (::bind(this->_socket, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)))
    throw TCPException(errno);
}

ISocketTCP		*SocketTCP::accept() {
  struct sockaddr_in	cs;
  socklen_t		lencs = sizeof(cs);
  int			socket;

  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  socket = ::accept(this->_socket, reinterpret_cast<struct sockaddr*>(&cs), &lencs);
  if (socket == INVALID_SOCKET)
    {
      if (this->_socket == INVALID_SOCKET)
	throw TCPException(errno);
    }
  return (new SocketTCP(socket));
}

void SocketTCP::connect(const std::string &address, const int port) {
  struct hostent*    hostinfo = NULL;
  struct sockaddr_in sin;

  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  if ((hostinfo = ::gethostbyname(address.c_str())) == NULL)
    throw TCPException("Gethostbyname as failed");
  sin.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  if (::connect(this->_socket, reinterpret_cast<struct sockaddr*>(&sin),
		sizeof(struct sockaddr)) < 0)
    throw TCPException(errno);
}

void SocketTCP::connect(const int address, const int port) {
  struct sockaddr_in sin;

  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  sin.sin_addr.s_addr = htonl(address);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  if (::connect(this->_socket, reinterpret_cast<struct sockaddr*>(&sin),
		sizeof(struct sockaddr)) < 0)
    throw TCPException(errno);
}

bool SocketTCP::send(IBuffer &buffer) {
  int ret;

  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  if ((ret = ::send(this->_socket, buffer.getBuffer() + buffer.getPosition(),
		    buffer.getLength() - buffer.getPosition(), MSG_NOSIGNAL)) == -1)
    throw TCPException(errno);
  buffer.setPosition(buffer.getPosition() + ret);
  return (buffer.end());
}

int SocketTCP::receive(IBuffer &buffer) {
  int ret;

  if (this->_socket == INVALID_SOCKET)
    throw TCPException(MSG_INVALID_SOCKET);
  if ((ret = ::recv(this->_socket, buffer.getBuffer() + buffer.getPosition(),
		    buffer.getMaxSize() - buffer.getPosition(), MSG_NOSIGNAL)) == -1)
    throw TCPException(errno);
  buffer.setLength(buffer.getLength() + ret);
  // buffer.setPosition(buffer.getLength());
  return (ret);
}

void SocketTCP::close() {
  ::close(this->_socket);
}

SocketTCP::~SocketTCP() {
  this->close();
}

#endif
