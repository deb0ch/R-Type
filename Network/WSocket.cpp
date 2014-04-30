#ifdef _WIN32

#include <iostream>
#include "WSocket.hh"

void Socket::init()
{
	std::cout << "init" << std::endl;
}

void Socket::close()
{
	std::cout << "close" << std::endl;
}

void Socket::send()
{
	std::cout << "send" << std::endl;
}

void Socket::recieve()
{
	std::cout << "recieve" << std::endl;
}

#endif