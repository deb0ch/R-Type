#ifndef		ISOCKETTCP_H_
# define	ISOCKETTCP_H_

# include <string>
# include <iostream>
# include "SocketFD.hh"
# include "ISocket.hh"

class ISocketTCP : public ISocket
{
public:
	virtual ~ISocketTCP(){};

public:
	virtual ISocketTCP	*accept() = 0;
	virtual void		listen(const std::size_t block) = 0;
	virtual void		bind(const int port, const std::string & address = "") = 0;
	virtual const int	getHandle() const = 0;

	virtual void		setBlocking(const bool blocking) = 0;
	virtual const bool	isBlocking() const = 0;

	virtual void		connect(const std::string &address, const int port) = 0;
	virtual void		connect(const int address, const int port) = 0;
	virtual int		send(const void* data, const std::size_t size) = 0;
	virtual int		receive(void* data, const std::size_t size) = 0;
	virtual void		close() = 0;
	virtual void		init() = 0;

};

#endif /* !ISOCKETTCP_H_ */
