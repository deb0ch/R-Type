#ifdef __linux__

# include "USocketTCP.hh"

SocketTCP::SocketTCP()
{
  this->close();
}

SocketTCP::~SocketTCP()
{
  this->close();
}

void SocketTCP::init()
{

}

void SocketTCP::setBlocking(bool const blocking)
{

}

const bool SocketTCP::isBlocking() const
{

  return (true);
}

void SocketTCP::connect(const std::string &address, const int port)
{
  struct hostent*    hostinfo = NULL;
  struct sockaddr_in sin;

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

void SocketTCP::connect(const int address, const int port)
{


}

void SocketTCP::send(const void* data, const std::size_t size)
{

}

void SocketTCP::receive(void* data, const std::size_t size,
					     std::size_t &received)
{

}

void SocketTCP::close()
{
  ::close(this->_socket);
}

#endif