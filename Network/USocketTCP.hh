#ifndef		USOCKETTCP_H_
# define	USOCKETTCP_H_

# include "ISocketTCP.hh"

class SocketTCP : public ISocketTCP
{

public:
  virtual ~SocketTCP();
  SocketTCP();

public:
  virtual void setBlocking(const bool blocking);
  virtual const bool isBlocking() const;
  virtual void close();
  virtual void init();

  virtual const ISocketTCP::Status connect(const std::string &address, const int port);
  virtual const ISocketTCP::Status connect(const int address, const int port);
  virtual const ISocketTCP::Status send(const void* data, const std::size_t size);
  virtual const ISocketTCP::Status receive(void* data, const std::size_t size,
					   std::size_t &received);
private:
  SocketTCP(const SocketTCP &);
  SocketTCP &operator=(const SocketTCP &);

};


#endif /* !USOCKETTCP_H_ */
