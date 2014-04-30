#ifdef __linux__

#include <iostream>
#include "USocket.hh"

void Socket::init()
{
	std::cout << "unix init" << std::endl;
}

void Socket::close()
{
	std::cout << "unix close" << std::endl;
}

void Socket::send()
{
	std::cout << "unix send" << std::endl;
}

void Socket::recieve()
{
	std::cout << "unix recieve" << std::endl;
}

#endif