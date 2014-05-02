#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "WSocketUDP.hh"

#pragma comment(lib, "ws2_32.lib")

SocketUDP::SocketUDP()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
	if (iResult != 0)
	{
		std::cerr << "startup failed" << std::endl;
		// exception
	}
	this->socket = INVALID_SOCKET;
}

SocketUDP::SocketUDP(const SOCKET &sock)
{
	this->socket = sock;
}

SocketUDP::~SocketUDP()
{
	WSACleanup();
}

void SocketUDP::init()
{
	char optval = 1;
	this->socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
	::setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (this->socket == INVALID_SOCKET)
	{
		std::cerr << "init failed" << std::endl;
		// Exception
	}
}

void SocketUDP::close()
{
	closesocket(this->socket);
}

void SocketUDP::bind(int port, const std::string &address)
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

int	SocketUDP::send(const void* data, const size_t size, const std::string & address, const int port)
{
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

	return (res);
}

int	SocketUDP::send(const void* data, const size_t size, const int address, const int port)
{
	sockaddr_in dest;
	int len_sockint = sizeof(dest);
	int res;

	dest.sin_port = ::htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = ::htonl(address);
	
	res = sendto(this->socket, reinterpret_cast<const char *>(data), size, 0,
		reinterpret_cast<struct sockaddr *>(&dest), len_sockint);

	return (res);
}

int	SocketUDP::receive(void* data, const size_t size,
	std::string& address, int& port)
{
	struct sockaddr_in src;
	int len_sockint = sizeof(src);

	int res = ::recvfrom(this->socket, reinterpret_cast<char *>(data),
		size, 0, reinterpret_cast<struct sockaddr *>(&src), &len_sockint);
	address = inet_ntoa(src.sin_addr);
	port = ntohs(src.sin_port);
	if (res == SOCKET_ERROR)
	{
		// Exception
		std::cerr << "recvfrom failed" << std::endl;
	}
	return (res);
}

void		SocketUDP::setBlocking(const bool blocking)
{
	this->blockSocket = blocking;
}

const bool	SocketUDP::isBlocking() const
{
	return (this->blockSocket);
}

#endif