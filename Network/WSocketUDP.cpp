#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "WSocketUDP.hh"
#include "UDPException.hh"

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
}

void SocketUDP::init()
{
	char optval = 1;
	this->socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
	::setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (this->socket == INVALID_SOCKET)
	{
		throw UDPException(WSAGetLastError());

	}
}

void SocketUDP::close()
{
	closesocket(this->socket);
}

void SocketUDP::bind(int port, const std::string &address)
{
	if (this->socket == INVALID_SOCKET)
		throw UDPException(MSG_INVALID_SOCKET);
	if (address == "")
		this->clientService.sin_addr.s_addr = ::htonl(INADDR_ANY);
	else
		this->clientService.sin_addr.s_addr = inet_addr(address.c_str());
	this->clientService.sin_family = AF_INET;
	if (WSAHtons(this->socket, port, &clientService.sin_port) != 0)
	{
		throw UDPException(WSAGetLastError());
	}
	if (::bind(this->socket, reinterpret_cast<sockaddr *>(&this->clientService),
		sizeof(this->clientService)) == SOCKET_ERROR)
	{
		throw UDPException("bind failed");
	}
}

int	SocketUDP::send(const IBuffer &data, const std::string & address, const int port)
{
	if (this->socket == INVALID_SOCKET)
		throw UDPException(MSG_INVALID_SOCKET);

	hostent* hostinfo = NULL;
	sockaddr_in dest;
	int len_sockint = sizeof(dest);
	int res;

	hostinfo = ::gethostbyname(address.c_str());
	dest.sin_port = ::htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr = *reinterpret_cast<in_addr*>(hostinfo->h_addr);

	res = sendto(this->socket, data.getBuffer(), data.getLength(), 0, reinterpret_cast<struct sockaddr *>(&dest), len_sockint);
	if (res == SOCKET_ERROR)
	{
		throw UDPException(WSAGetLastError());
	}
	return (res);
}

int	SocketUDP::send(const IBuffer &data, const int address, const int port)
{
	if (this->socket == INVALID_SOCKET)
		throw UDPException(MSG_INVALID_SOCKET);

	sockaddr_in dest;
	int len_sockint = sizeof(dest);
	int res;

	dest.sin_port = ::htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = ::htonl(address);

	res = sendto(this->socket, data.getBuffer(), data.getLength(), 0,
		reinterpret_cast<struct sockaddr *>(&dest), len_sockint);
	if (res == SOCKET_ERROR)
	{
		throw UDPException(WSAGetLastError());
	}
	return (res);
}

int	SocketUDP::receive(IBuffer &data, std::string& address, int& port)
{

	if (this->socket == INVALID_SOCKET)
		throw UDPException(MSG_INVALID_SOCKET);

	struct sockaddr_in src;
	int len_sockint = sizeof(src);

	int res = ::recvfrom(this->socket, data.getBuffer(), data.getMaxSize(), 0, reinterpret_cast<struct sockaddr *>(&src), &len_sockint);
	address = inet_ntoa(src.sin_addr);
	port = ntohs(src.sin_port);
	if (res == SOCKET_ERROR)
	{
		throw UDPException(WSAGetLastError());
	}
	data.setLength(res);
	data.rewind();
	return (res);
}

void		SocketUDP::setBlocking(const bool block)
{
	if (this->socket == INVALID_SOCKET)
	{
		throw UDPException(MSG_INVALID_SOCKET);
	}
	u_long blocking = block ? 0 : 1;
	this->blockSocket = block;
	ioctlsocket(this->socket, FIONBIO, &blocking);
}

bool	SocketUDP::isBlocking() const
{
	return (this->blockSocket);
}

int	SocketUDP::getHandle() const
{
	return (this->socket);
}

#endif /* !_WIN32 */
