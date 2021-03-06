#ifndef		ISOCKETUDP_H_
# define	ISOCKETUDP_H_

# include <string>
# include <iostream>
# include "ISocket.hh"
# include "IBuffer.hh"

class ISocketUDP : public ISocket
{
public:
  virtual ~ISocketUDP(){};

public:
  virtual void		setBlocking(const bool blocking) = 0;
  virtual bool	isBlocking() const = 0;
  virtual int	getHandle() const = 0;

  virtual void	bind(const int port, const std::string &address = "") = 0;
  virtual int	send(const IBuffer &, const int address, const int port) = 0;
  virtual int	send(const IBuffer &, const std::string & address, const int port) = 0;
  virtual int	receive(IBuffer &, std::string& address, int& port) = 0;
  virtual void	close() = 0;
  virtual void	init() = 0;

};


#endif /* !ISOCKETUDP_H_ */
