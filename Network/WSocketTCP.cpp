#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "WSocketTCP.hh"
#include <signal.h>

#pragma comment(lib, "ws2_32.lib")

SocketTCP::SocketTCP()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
	if (iResult != 0)
	{
		std::cerr << "startup failed" << std::endl;
		// exception
	}
	this->blockingSocket = false;
	this->socket = INVALID_SOCKET;
}

SocketTCP::SocketTCP(const SOCKET &sock)
{
	this->socket = sock;
}

SocketTCP::~SocketTCP()
{
	WSACleanup();
}

int SocketTCP::send(const void* data, const std::size_t size)
{
	int res = ::send(this->socket, reinterpret_cast<const char *>(data),
		size, 0);
	if (res == SOCKET_ERROR)
	{
		std::cerr << "send failed" << std::endl;
		// Exception
	}
	return (res);
}

int SocketTCP::receive(void* data, const std::size_t size)
{
	int received = ::recv(this->socket, reinterpret_cast<char *>(data), size, 0);
	if (received == SOCKET_ERROR)
	{
		std::cerr << "recv failed" << std::endl;
		// Exception
	}
	return (received);
}

void SocketTCP::listen(const std::size_t block)
{
	if (::listen(this->socket, block) == SOCKET_ERROR)
	{
		std::cerr << "listen failed" << std::endl;
		// Exception
	}
}

void SocketTCP::close()
{
	closesocket(this->socket);
}

ISocketTCP *SocketTCP::accept()
{
	sockaddr_in cs;
	int			lencs = sizeof(cs);
	SOCKET		sock;

	sock = WSAAccept(this->socket, reinterpret_cast<SOCKADDR*>(&cs), &lencs, NULL, NULL);
	//sock = ::accept(this->socket, NULL, NULL);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "accept() failed." << std::endl;
		return (NULL);
	}
	return (new SocketTCP(sock));
}

void SocketTCP::bind(int port, const std::string &address)
{
	if (address == "")
			this->clientService.sin_addr.s_addr = ::htonl(INADDR_ANY);
	else
		this->clientService.sin_addr.s_addr = inet_addr(address.c_str());
	this->clientService.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &clientService.sin_port) != 0)
	{
		// Exception
		std::cerr << "WSAHTONS failed" << std::endl;
	}
	if (::bind(this->socket, reinterpret_cast<sockaddr *>(&this->clientService),
		sizeof(this->clientService)) == SOCKET_ERROR)
	{
		// Exception
		std::cerr << "bind failed" << std::endl;
	}
}

void SocketTCP::connect(const std::string &address, const int port)
{
	hostent*		hostinfo = NULL;
	sockaddr_in		sock_in;

	hostinfo = ::gethostbyname(address.c_str());
	if (hostinfo == NULL)
		std::cerr << "connection failure." << std::endl;
	sock_in.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
	sock_in.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &sock_in.sin_port) != 0)
		std::cerr << "ERROR on attribuate port on ip." << std::endl;
	if (::connect(this->socket, reinterpret_cast<struct sockaddr*>(&sock_in), sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		std::cerr << "connect failed." << std::endl;
	}
}

void SocketTCP::connect(const int address, const int port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = ::htonl(address);
	clientService.sin_port = htons(port);
	if (::connect(this->socket, reinterpret_cast<SOCKADDR *>(&clientService),
		sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cerr << "connect failed" << std::endl;
		// Exception
	}
}

void SocketTCP::init()
{
	this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->socket == INVALID_SOCKET)
	{
		std::cerr << "init failed" << std::endl;
		// Exception
	}
}

const bool	SocketTCP::isBlocking() const
{
	return (this->blockingSocket);
}

void SocketTCP::setBlocking(bool const block)
{
	u_long blocking = block ? 0 : 1;
	this->blockingSocket = block;
	ioctlsocket(this->socket, FIONBIO, &blocking);
}

#endif