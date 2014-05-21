#include <iostream>
#ifdef _WIN32
	#include "WSocketTCP.hh"
#elif __linux__
	#include "USocketTCP.hh"
#endif

int main()
{
	std::cout << "toto" << std::endl;
	ISocket *toto = new SocketTCP();
	delete toto;
}
