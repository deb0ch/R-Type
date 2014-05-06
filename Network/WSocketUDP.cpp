#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "WSocketUDP.hh"
#include "NetworkException.hh"

#pragma comment(lib, "ws2_32.lib")

SocketUDP::SocketUDP()
{
	this->socket = INVALID_SOCKET;
	this->blockSocket = false;
}

SocketUDP::SocketUDP(const SOCKET &sock)
{
	this->socket = sock;
	this->blockSocket = false;
}

SocketUDP::~SocketUDP()
{
	WSACleanup();
}

void SocketUDP::init()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
	if (iResult != 0)
	{
		throw NetworkException(NetworkException::UDP, WSAGetLastError(),
			NetworkException::SEVERITY::S_ERROR);
	}
	char optval = 1;
	this->socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
	::setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (this->socket == INVALID_SOCKET)
	{
		throw NetworkException(NetworkException::UDP, WSAGetLastError(),
			NetworkException::SEVERITY::S_ERROR);

	}
}

void SocketUDP::close()
{
	closesocket(this->socket);
}

void SocketUDP::bind(int port, const std::string &address)
{
	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::UDP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);
	if (address == "")
		this->clientService.sin_addr.s_addr = ::htonl(INADDR_ANY);
	else
		this->clientService.sin_addr.s_addr = inet_addr(address.c_str());
	this->clientService.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &clientService.sin_port) != 0)
	{
		throw NetworkException(NetworkException::UDP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	if (::bind(this->socket, reinterpret_cast<sockaddr *>(&this->clientService),
		sizeof(this->clientService)) == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::UDP, "bind failed",
			NetworkException::S_ERROR);
	}
}

int	SocketUDP::send(const void* data, const size_t size, const std::string & address, const int port)
{
	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::UDP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);

	hostent* hostinfo = NULL;
	sockaddr_in dest;
	int len_sockint = sizeof(dest);
	int res;

	hostinfo = ::gethostbyname(address.c_str());
	dest.sin_port = ::htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);

	res = sendto(this->socket, reinterpret_cast<const char *>(data), size, 0,
		reinterpret_cast<struct sockaddr *>(&dest), len_sockint);
	if (res == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::UDP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	return (res);
}

int	SocketUDP::send(const void* data, const size_t size, const int address, const int port)
{
	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::UDP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);

	sockaddr_in dest;
	int len_sockint = sizeof(dest);
	int res;

	dest.sin_port = ::htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = ::htonl(address);

	res = sendto(this->socket, reinterpret_cast<const char *>(data), size, 0,
		reinterpret_cast<struct sockaddr *>(&dest), len_sockint);
	if (res == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::UDP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	return (res);
}

int	SocketUDP::receive(void* data, const size_t size,
	std::string& address, int& port)
{

	if (this->socket == INVALID_SOCKET)
		throw NetworkException(NetworkException::UDP, MSG_INVALID_SOCKET,
		NetworkException::S_WARNING);

	struct sockaddr_in src;
	int len_sockint = sizeof(src);

	int res = ::recvfrom(this->socket, reinterpret_cast<char *>(data),
		size, 0, reinterpret_cast<struct sockaddr *>(&src), &len_sockint);
	address = inet_ntoa(src.sin_addr);
	port = ntohs(src.sin_port);
	if (res == SOCKET_ERROR)
	{
		throw NetworkException(NetworkException::UDP, WSAGetLastError(),
			NetworkException::S_ERROR);
	}
	return (res);
}

void		SocketUDP::setBlocking(const bool block)
{
	if (this->socket == INVALID_SOCKET)
	{
		throw NetworkException(NetworkException::UDP, MSG_INVALID_SOCKET,
			NetworkException::SEVERITY::S_WARNING);;
	}
	u_long blocking = block ? 0 : 1;
	this->blockSocket = block;
	ioctlsocket(this->socket, FIONBIO, &blocking);
}

const bool	SocketUDP::isBlocking() const
{
	return (this->blockSocket);
}

const int	SocketUDP::getHandle() const
{
	return (this->socket);
}

#endif /* !_WIN32 */
