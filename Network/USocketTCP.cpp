
# include "USocketTCP.hh"

SocketTCP::SocketTCP()
{
  this->close();
}

SocketTCP::~SocketTCP()
{
  this->close();
}

void SocketTCP::setBlocking(bool const blocking)
{

}

const bool SocketTCP::isBlocking() const
{

}

void SocketTCP::close()
{

}

void SocketTCP::init()
{

}

const ISocketTCP::Status SocketTCP::connect(const std::string &address, const int port)
{

}

const ISocketTCP::Status SocketTCP::connect(const int address, const int port)
{


}

const ISocketTCP::Status SocketTCP::send(const void* data, const std::size_t size)
{

}

const ISocketTCP::Status SocketTCP::receive(void* data, const std::size_t size,
					     std::size_t &received)
{

}
