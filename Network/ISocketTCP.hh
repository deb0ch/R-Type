#ifndef		ISOCKETTCP_H_
# define	ISOCKETTCP_H_

# include <string>
# include "SocketFD.hh"

class ISocketTCP
{

public:
  enum Status
    {
      Done,         ///< The socket has sent / received the data
      NotReady,     ///< The socket is not ready to send / receive data yet
      Disconnected, ///< The TCP socket has been disconnected
      Error         ///< An unexpected error happened
    };

  enum
    {
      AnyPort = 0 ///< Special value that tells the system to pick any available port
    };

public:
  virtual ~ISocketTCP(){};

public:
  virtual void		setBlocking(bool const blocking) = 0;
  virtual bool		isBlocking() const = 0;
  virtual const Status	connect(const std::string &address, const int port) = 0;
  virtual const Status	connect(const int address, const int port) = 0;
  virtual const Status	send(const void* data, const std::size_t size) = 0;
  virtual const Status	receive(void* data, const std::size_t size,
				std::size_t &received) = 0;
  virtual void		close() = 0;
  virtual void		init() = 0;

};

#endif /* !ISOCKETTCP_H_ */
