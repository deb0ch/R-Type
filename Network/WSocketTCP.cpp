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
		std::cerr << "startup failed" << std::endl;
		// exception
	}
	this->socket = INVALID_SOCKET;
}

SocketTCP::~SocketTCP()
{
	WSACleanup();
}

int SocketTCP::send(const void* data, const std::size_t size)
{
	int res = ::send(this->socket, reinterpret_cast<const char *>(data), size, 0);
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

void SocketTCP::setSocket(const SOCKET sock)
{
	this->socket = sock;
}

ISocketTCP *SocketTCP::accept()
{
	SOCKET result = ::accept(this->socket, NULL, NULL);
	if (result == INVALID_SOCKET)
	{
		std::cerr << "accept failed" << std::endl;
		// Exception
	}
//	try
//	{
		SocketTCP* res = new SocketTCP();
//	}
//	catch (/* Exception */)
//	{

//	}
	res->setSocket(result);
	return (res);
}

void SocketTCP::bind(int port, const std::string &address)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(address.c_str());
	clientService.sin_port = htons(port);
	if (::bind(this->socket, reinterpret_cast<sockaddr *>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cerr << "bind failed" << std::endl;
		// Exception
	}
}

void SocketTCP::connect(const std::string &address, const int port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(address.c_str());
	clientService.sin_port = htons(port);
	if (::connect(this->socket, reinterpret_cast<SOCKADDR *>(&clientService),
		sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cerr << "connect failed" << std::endl;
		// Exception
	}
}

void SocketTCP::connect(const int address, const int port)
{
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = address;
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

const bool SocketTCP::isBlocking() const
{
	return (true);
}

void SocketTCP::setBlocking(bool const blocking)
{

}

#endif