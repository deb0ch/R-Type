#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstdlib>
#include <cerrno>
#include "WSocketTCP.hh"
#include "TCPException.hh"

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
}

int		SocketTCP::getHandle() const
{
	return (this->socket);
}

bool SocketTCP::send(IBuffer &data)
{
	if (this->socket == INVALID_SOCKET)
	  throw TCPException(MSG_INVALID_SOCKET);
	int res = ::send(this->socket, data.getBuffer() + data.getPosition(),
			 data.getLength() - data.getPosition(), 0);
	if (res == SOCKET_ERROR)
	{
		throw TCPException(WSAGetLastError());
	}
	data.setPosition(data.getPosition() + res);
	return (data.end());
}

int SocketTCP::receive(IBuffer &data)
{
	if (this->socket == INVALID_SOCKET)
	  throw TCPException(MSG_INVALID_SOCKET);
	int received = ::recv(this->socket, data.getBuffer() + data.getPosition(),
			      data.getMaxSize() - data.getPosition(), 0);
	if (received == SOCKET_ERROR)
	{
		throw TCPException(WSAGetLastError());
	}
	data.setLength(data.getLength() + received);
	// data.setPosition(data.getLength());
	return (received);
}

void SocketTCP::listen(const std::size_t block)
{
	if (::listen(this->socket, block) == SOCKET_ERROR)
	{
		throw TCPException(" listen failed");
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
		throw TCPException(MSG_INVALID_SOCKET);
	sock = WSAAccept(this->socket, reinterpret_cast<SOCKADDR*>(&cs), &lencs, NULL, NULL);
	if (sock == INVALID_SOCKET)
	{
		throw TCPException(WSAGetLastError());
	}
	return (new SocketTCP(sock));
}

void SocketTCP::bind(int port, const std::string &address)
{
	if (this->socket == INVALID_SOCKET)
		throw TCPException(MSG_INVALID_SOCKET);
	if (address == "")
		this->clientService.sin_addr.s_addr = ::htonl(INADDR_ANY);
	else
		this->clientService.sin_addr.s_addr = inet_addr(address.c_str());
	this->clientService.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &clientService.sin_port) != 0)
	{
		throw TCPException(WSAGetLastError());
	}
	if (::bind(this->socket, reinterpret_cast<sockaddr *>(&this->clientService),
		sizeof(this->clientService)) == SOCKET_ERROR)
	{
		throw TCPException("bind failed");
	}
}

void SocketTCP::connect(const std::string &address, const int port)
{
	hostent*		hostinfo = NULL;
	sockaddr_in		sock_in;

	if (this->socket == INVALID_SOCKET)
		throw TCPException(MSG_INVALID_SOCKET);
	hostinfo = ::gethostbyname(address.c_str());
	if (hostinfo == NULL)
		throw TCPException("gethostbyname failed");
	sock_in.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);
	sock_in.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &sock_in.sin_port) != 0)
		throw TCPException(WSAGetLastError());
	if (::connect(this->socket, reinterpret_cast<struct sockaddr*>(&sock_in), sizeof(struct sockaddr)) == SOCKET_ERROR)
	{
		throw TCPException(WSAGetLastError());
	}
}

void SocketTCP::connect(const int address, const int port)
{
	if (this->socket == INVALID_SOCKET)
		throw TCPException(MSG_INVALID_SOCKET);
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = ::htonl(address);
	clientService.sin_port = htons(port);
	if (::connect(this->socket, reinterpret_cast<SOCKADDR *>(&clientService),
		sizeof(clientService)) == SOCKET_ERROR)
	{
		throw TCPException(WSAGetLastError());
	}
}

void SocketTCP::init()
{
	int reuseAddr = 1;
	this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->socket == INVALID_SOCKET)
	{
		throw TCPException(WSAGetLastError());
	}
	//::setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR &reuseAddr, sizeof(reuseAddr));
}

bool	SocketTCP::isBlocking() const
{
	return (this->blockingSocket);
}

void SocketTCP::setBlocking(bool const block)
{
	if (this->socket == INVALID_SOCKET)
	{
		throw TCPException(MSG_INVALID_SOCKET);;
	}
	u_long blocking = block ? 0 : 1;
	this->blockingSocket = block;
	ioctlsocket(this->socket, FIONBIO, &blocking);
}

#endif
