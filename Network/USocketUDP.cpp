#ifdef __linux__

#include <fcntl.h>
#include "USocketUDP.hh"

static const int INVALIDE_SOCKET = -1;

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
  if (this->_socket < 0) {
    //TODO throw
    std::cerr << "socket() failed." << std::endl;
  }
}

void		SocketUDP::bind(const int port, const std::string & address) {
  struct hostent*    hostinfo = NULL;
  struct sockaddr_in sin;

  if (address == "")
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
  else
    {
      hostinfo = ::gethostbyname(address.c_str());
      if (hostinfo == NULL)
	std::cerr << "bind didn't know this host." << std::endl; //TODO throw
      sin.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if (::bind(this->_socket, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)))
    std::cerr << "bind() failed." << std::endl; //TODO throw
}

int	SocketUDP::send(const void* data, const size_t size, const int address, const int port) {
  struct sockaddr_in to;

  to.sin_addr.s_addr = htonl(address);
  to.sin_port = htons(port);
  to.sin_family = AF_INET;

  int s = ::sendto(this->_socket, data, size, MSG_NOSIGNAL,
		   reinterpret_cast<struct sockaddr*>(&to), sizeof(struct sockaddr));
  if (s == -1)
    s = -1; //TODO throw;
  return (s);
}

int	SocketUDP::send(const void* data, const size_t size,
			const std::string & address, const int port) {
  struct sockaddr_in	to;
  struct hostent	*hostinfo = NULL;
  int			s;

  hostinfo = ::gethostbyname(address.c_str());
  if (hostinfo == NULL)
    std::cerr << "connection failure." << std::endl;
  to.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
  to.sin_port = htons(port);
  to.sin_family = AF_INET;

  s = ::sendto(this->_socket, data, size, MSG_NOSIGNAL,
	       reinterpret_cast<struct sockaddr*>(&to), sizeof(struct sockaddr));
  if (s == -1)
    s = -1; //TODO throw;
  return (s);
}

int	SocketUDP::receive(void* data, const size_t size, std::string &address, int &port) {
  struct sockaddr_in	from;
  socklen_t		lenfrom = sizeof(from);

  int s = ::recvfrom(this->_socket, data, size, 0, reinterpret_cast<struct sockaddr*>(&from), &lenfrom);
  if (s == -1)
    s = -1; //TODO throw; SocketException(errno);
  address = ::inet_ntoa(from.sin_addr);
  port = ::ntohs(from.sin_port);
  return (s);
}

void SocketUDP::setBlocking(bool const blocking) {
  int status = ::fcntl(this->_socket, F_GETFL);

  if (this->_socket == INVALIDE_SOCKET)
    return ; //TODO throw
  if (blocking)
    ::fcntl(this->_socket, F_SETFL, status & ~O_NONBLOCK);
  else
    ::fcntl(this->_socket, F_SETFL, status | O_NONBLOCK);
  this->_isBlocking = blocking;
}

const bool SocketUDP::isBlocking() const {
  return (this->_isBlocking);
}


void SocketUDP::close() {
  ::close(this->_socket);
}

SocketUDP::~SocketUDP() {
  this->close();
}

#endif
