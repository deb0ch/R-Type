#ifdef _WIN32

#include <iostream>
#include "WSocket.hh"

void Socket::init()
{
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