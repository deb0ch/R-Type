#ifndef		WSOCKETTCP_H_
# define	WSOCKETTCP_H_

# include <Windows.h>
# include <string>
# include "ISocketTCP.hh"
# include "IBuffer.hh"

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
	virtual int getHandle() const;

	virtual bool isBlocking() const;
	virtual void close();
	virtual void init();

	virtual void connect(const std::string &address, const int port);
	virtual void connect(const int address, const int port);
	virtual bool	send(IBuffer &);
	virtual int receive(IBuffer &);
private:
	SocketTCP(const SocketTCP &);
	SocketTCP &operator=(const SocketTCP &);
};


#endif /* !WSOCKETTCP_H_ */
