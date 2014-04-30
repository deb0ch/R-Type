#ifndef		ISOCKETTCP_H_
# define	ISOCKETTCP_H_

# include <string>
# include <iostream>
# include "SocketFD.hh"

class ISocketTCP
{

public:
  enum
    {
      AnyPort = 0 ///< Special value that tells the system to pick any available port
    };

public:
  virtual ~ISocketTCP(){};

public:
  virtual ISocketTCP	*accept() = 0;
  virtual void		listen(uint32_t block) = 0;
  virtual void		bind(int port, std::string address = "") = 0;
  virtual void		setBlocking(bool const blocking) = 0;
  virtual const bool	isBlocking() const = 0;
  virtual void		connect(const std::string &address, const int port) = 0;
  virtual void		connect(const int address, const int port) = 0;
  virtual void		send(const void* data, const std::size_t size) = 0;
  virtual void		receive(void* data, const std::size_t size,
				std::size_t &received) = 0;
  virtual void		close() = 0;
  virtual void		init() = 0;

};

#endif /* !ISOCKETTCP_H_ */
