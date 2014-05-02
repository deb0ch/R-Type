#ifndef		WSOCKETTCP_H_
# define	WSOCKETTCP_H_

# include <Windows.h>
# include <string>
# include "ISocketTCP.hh"

class SocketTCP : public ISocketTCP
{
private:
	SOCKET socket;
	WSADATA wsaData;
	struct addrinfo *ptr;

public:
	SocketTCP();
	~SocketTCP();

	virtual ISocketTCP	*accept();
	virtual void listen(const std::size_t block);
	virtual void bind(int port, const std::string & address = "");
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
	const struct addrinfo *getaddrfrom(const int address, const int port);
	const struct addrinfo *getaddrfrom(const std::string &address, const int port);
	void setSocket(const SOCKET sock);
};


#endif /* !USOCKETTCP_H_ */
