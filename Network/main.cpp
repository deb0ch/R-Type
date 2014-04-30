#include <iostream>

#ifdef __linux__ 
#include "USocketTCP.hh"
#include <unistd.h>
#elif _WIN32
#include "WSocketTCP.hh"
#include <Windows.h>
#endif

int	main()
{
	ISocketTCP *sock = new SocketTCP();

#ifdef __linux__ 
	sleep(5);
#elif _WIN32
	Sleep(5000);
#endif
}