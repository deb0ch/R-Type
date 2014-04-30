#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "WSocketTCP.hh"

#pragma comment(lib, "ws2_32.lib")

SocketTCP::SocketTCP()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &(this->wsaData));
	if (iResult != 0)
	{
		// exception
	}
	this->socket = INVALID_SOCKET;
}

SocketTCP::~SocketTCP()
{
	WSACleanup();
}

ISocketTCP	*accept() = 0;
void		listen(const std::size_t block)
{

}
void		bind(int port, std::string address = "") ;

void SocketTCP::setBlocking(bool const blocking)
{

}

const bool SocketTCP::isBlocking() const
{
	return (true);
}

void SocketTCP::close()
{
	closesocket(this->socket);
}

void SocketTCP::init()
{
}

void SocketTCP::connect(const std::string &address, const int port)
{
}

void SocketTCP::connect(const int address, const int port)
{
}

void SocketTCP::send(const void* data, const std::size_t size)
{
	if (::send(this->socket, (char *)data, size, 0) == SOCKET_ERROR)
	{
		// Exception
	}
}

void SocketTCP::receive(void* data, const std::size_t size,
						std::size_t &received)
{
	received = ::recv(this->socket, (char *)data, size, 0);
	if (received > 0)
	{
		// Exception
	}
	else if (received == 0)
	{
		// Exception
	}
	else
	{
		// Ok
	}
}

#endif