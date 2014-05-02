#ifndef		WSOCKETTCP_H_
# define	WSOCKETTCP_H_

# include <Windows.h>
# include <string>
# include "ISocketTCP.hh"

class SocketTCP : public ISocketTCP
{
private:
	bool blockingSocket;
	SOCKET socket;
	WSADATA wsaData;
	struct sockaddr_in clientService;
	SocketTCP(const SOCKET &sock);

public:
	SocketTCP();
	~SocketTCP();

	virtual ISocketTCP	*accept();
	virtual void listen(const std::size_t block);
	virtual void bind(const int port, const std::string & address = "");
	virtual void setBlocking(bool const blocking);
	virtual const bool	isBlocking() const;
	virtual void close();
	virtual void init();

	virtual void connect(const std::string &address, const int port);
	virtual void connect(const int address, const int port);
	virtual int send(const void* data, const std::size_t size);
	virtual int receive(void* data, const std::size_t size);
private:
	SocketTCP(const SocketTCP &);
	SocketTCP &operator=(const SocketTCP &);
	const struct addrinfo *getaddrfrom(const int address, const int port);
	const struct addrinfo *getaddrfrom(const std::string &address, const int port);
};


#endif /* !USOCKETTCP_H_ */
