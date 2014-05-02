#ifdef __linux__

#include <fcntl.h>
#include "USocketTCP.hh"

static const int INVALIDE_SOCKET = -1;

SocketTCP::SocketTCP() {
  this->_isBlocking = true;
}

SocketTCP::~SocketTCP() {
  this->close();
}

void SocketTCP::init() {
  //TODO
}

void SocketTCP::setBlocking(bool const blocking) {
  int status = ::fcntl(this->_socket, F_GETFL);

  if (this->_socket == INVALIDE_SOCKET)
    return ; //TODO throw
  if (blocking)
    ::fcntl(this->_socket, F_SETFL, status & ~O_NONBLOCK);
  else
    ::fcntl(this->_socket, F_SETFL, status | O_NONBLOCK);
  this->_isBlocking = blocking;
}

const bool SocketTCP::isBlocking() const {
  return (this->_isBlocking);
}

void SocketTCP::connect(const std::string &address, const int port) {
  struct hostent*    hostinfo = NULL;
  struct sockaddr_in sin;

  if (this->_socket == INVALIDE_SOCKET)
    return ; //TODO throw
  hostinfo = ::gethostbyname(address.c_str());
  if (hostinfo == NULL)
    std::cerr << "connection failure." << std::endl;
  sin.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  if (::connect(this->_socket, reinterpret_cast<struct sockaddr*>(&sin),
		sizeof(struct sockaddr)) < 0)
    {
      std::cerr << "//TODO throw connect() failed." << std::endl;
    }
}

void SocketTCP::connect(const int address, const int port) {
  struct sockaddr_in sin;

  if (this->_socket == INVALIDE_SOCKET)
    return ; //TODO throw
  sin.sin_addr.s_addr = htonl(address);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  if (::connect(this->_socket, reinterpret_cast<struct sockaddr*>(&sin),
		sizeof(struct sockaddr)) < 0)
    {
      std::cerr << "//TODO throw connect() failed." << std::endl;
    }
}

int SocketTCP::send(const void* data, const std::size_t size) {
  int ret = ::send(this->_socket, data, size, 0);

  if (ret == -1)
    ret = -1 ;//TODO throw exection
  return (ret);
}

int SocketTCP::receive(void* data, const std::size_t size,
		       std::size_t &received) {
  int ret = ::recv(this->_socket, data, size, 0);

  if (ret == -1)
    ret = -1 ;//TODO throw exection
  return (ret);
}

void SocketTCP::close() {
  ::close(this->_socket);
}

#endif
