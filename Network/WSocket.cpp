#ifdef _WIN32

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "WSocket.hh"

#pragma comment(lib, "ws2_32.lib")

void Socket::init()
{
	WORD wVersionRequested;

	wVersionRequested = MAKEWORD(2, 2);
	int res = WSAStartup(wVersionRequested, &(this->wsaData));
	if (res != 0)
	{
		// Class d'exception a faire
		std::cerr << "WSAStartup failed: " << res << std::endl;
	}
	std::cout << "win init" << std::endl;
}

void Socket::close()
{
	std::cout << "win close" << std::endl;
}

void Socket::send()
{
	std::cout << "win send" << std::endl;
}

void Socket::recieve()
{
	std::cout << "win recieve" << std::endl;
}

#endif