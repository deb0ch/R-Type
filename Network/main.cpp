#include <iostream>

#ifdef __linux__ 
#include "USocket.hh"
#include <unistd.h>
#elif _WIN32
#include "WSocket.hh"
#include <Windows.h>
#endif

int	main()
{
	ISocket *sock = new Socket();

	sock->init();
	sock->send();
	sock->recieve();
	sock->close();

#ifdef __linux__ 
	sleep(5);
#elif _WIN32
	Sleep(5000);
#endif
}