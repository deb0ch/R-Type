#ifndef		USOCKETTCP_H_
# define	USOCKETTCP_H_

# include "ISocketTCP.hh"

class USocketTCP : public ISocketTCP
{

public:
  virtual ~USocketTCP(){};

public:
  virtual void setBlocking(bool const blocking);
  virtual bool isBlocking() const;
  virtual void close();
  virtual void init();

  virtual const ISocketTCP::Status connect(const std::string &address, const int port);
  virtual const ISocketTCP::Status connect(const int address, const int port);
  virtual const ISocketTCP::Status send(const void* data, const std::size_t size);
  virtual const ISocketTCP::Status receive(void* data, const std::size_t size,
					   std::size_t &received);
private:
  USocketTCP(const USocketTCP &);
  USocketTCP &operator=(const USocketTCP &);

};


#endif /* !USOCKETTCP_H_ */
