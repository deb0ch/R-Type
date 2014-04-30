#ifndef		WSOCKETTCP_H_
# define	WSOCKETTCP_H_

# include <Windows.h>
# include "ISocketTCP.hh"

class SocketTCP : public ISocketTCP
{
private:
	SOCKET socket;
	WSADATA wsaData;

public:
	SocketTCP();
	~SocketTCP();

	virtual ISocketTCP	*accept() = 0;
	virtual void		listen(const std::size_t block) = 0;
	virtual void		bind(int port, std::string address = "") = 0;
	virtual void setBlocking(bool const blocking);
	virtual const bool isBlocking() const;
	virtual void close();
	virtual void init();

	virtual void connect(const std::string &address, const int port);
	virtual void connect(const int address, const int port);
	virtual void send(const void* data, const std::size_t size);
	virtual void receive(void* data, const std::size_t size,
		std::size_t &received);
private:
	SocketTCP(const SocketTCP &);
	SocketTCP &operator=(const SocketTCP &);
};


#endif /* !USOCKETTCP_H_ */
