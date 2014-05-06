#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <errno.h>
#include "WSocketTCP.hh"
#include "NetworkException.hh"

#pragma comment(lib, "ws2_32.lib")

SocketTCP::SocketTCP()
{
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

const int		SocketTCP::getHandle() const
{
	return (this->socket);
}

int SocketTCP::send(const IBuffer &data)
{
	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::TCP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);
	int res = ::send(this->socket, data.getBuffer(), data.getLength(), 0);
	if (res == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	return (res);
}

int SocketTCP::receive(void* data, const std::size_t size)
{
	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::TCP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);
	int received = ::recv(this->socket, reinterpret_cast<char *>(data), size, 0);
	if (received == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	return (received);
}

void SocketTCP::listen(const std::size_t block)
{
	if (::listen(this->socket, block) == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::TCP, " listen failed",
			NetworkException::SEVERITY::S_WARNING);;
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

	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::TCP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);
	sock = WSAAccept(this->socket, reinterpret_cast<SOCKADDR*>(&cs), &lencs, NULL, NULL);
	if (sock == INVALID_SOCKET)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	return (new SocketTCP(sock));
}

void SocketTCP::bind(int port, const std::string &address)
{
	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::TCP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);
	if (address == "")
		this->clientService.sin_addr.s_addr = ::htonl(INADDR_ANY);
	else
		this->clientService.sin_addr.s_addr = inet_addr(address.c_str());
	this->clientService.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &clientService.sin_port) != 0)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	if (::bind(this->socket, reinterpret_cast<sockaddr *>(&this->clientService),
		sizeof(this->clientService)) == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::TCP, "bind failed",
			NetworkException::S_ERROR);
	}
}

void SocketTCP::connect(const std::string &address, const int port)
{
	hostent*		hostinfo = NULL;
	sockaddr_in		sock_in;

	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::TCP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);
	hostinfo = ::gethostbyname(address.c_str());
	if (hostinfo == NULL)
		throw NetworkException(NetworkException::TCP, "gethostbyname failed",
		NetworkException::S_ERROR);
	sock_in.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
	sock_in.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &sock_in.sin_port) != 0)
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
		NetworkException::S_ERROR);
	if (::connect(this->socket, reinterpret_cast<struct sockaddr*>(&sock_in), sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
}

void SocketTCP::connect(const int address, const int port)
{
	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::TCP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = ::htonl(address);
	clientService.sin_port = htons(port);
	if (::connect(this->socket, reinterpret_cast<SOCKADDR *>(&clientService),
		sizeof(clientService)) == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
}

void SocketTCP::init()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
	int reuseAddr = 1;
	if (iResult != 0)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::SEVERITY::S_ERROR);
	}
	this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->socket == INVALID_SOCKET)
	{
		throw NetworkException(NetworkException::TCP, WSAGetLastError(),
			NetworkException::SEVERITY::S_ERROR);;
	}
	//::setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR &reuseAddr, sizeof(reuseAddr));
}

const bool	SocketTCP::isBlocking() const
{
	return (this->blockingSocket);
}

void SocketTCP::setBlocking(bool const block)
{
	if (this->socket == INVALID_SOCKET)
	{
		throw NetworkException(NetworkException::TCP, MSG_INVALID_SOCKET,
			NetworkException::SEVERITY::S_WARNING);;
	}
	u_long blocking = block ? 0 : 1;
	this->blockingSocket = block;
	ioctlsocket(this->socket, FIONBIO, &blocking);
}

#endif