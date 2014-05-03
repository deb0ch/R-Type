#ifndef		ISOCKETUDP_H_
# define	ISOCKETUDP_H_

# include <string>
# include <iostream>
# include "ISocket.hh"

class ISocketUDP : public ISocket
{
public:
  virtual ~ISocketUDP(){};

public:
  virtual void		setBlocking(const bool blocking) = 0;
  virtual const bool	isBlocking() const = 0;
  virtual const int		getHandle() const = 0;

  virtual void	bind(const int port, const std::string &address = "") = 0;
  virtual int	send(const void* data, const size_t size, const int address, const int port) = 0;
  virtual int	send(const void* data, const size_t size, const std::string & address, const int port) = 0;
  virtual int	receive(void* data, const size_t size, std::string& address, int& port) = 0;
  virtual void	close() = 0;
  virtual void	init() = 0;

};


#endif /* !ISOCKETUDP_H_ */
