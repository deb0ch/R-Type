#include <iostream>

#ifdef __linux__
#include "USocketTCP.hh"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#elif _WIN32
#include "WSocketTCP.hh"
#include <Windows.h>
#endif

#define IPADRESS "127.0.0.1"
#define PORT 6667

void testclient()
{
	ISocketTCP *sock = new SocketTCP();
	char sendmsg[] = "i am the client !";
	sock->init();
	sock->connect(IPADRESS, PORT);
	char toto[42];
	sock->send(sendmsg, strlen(sendmsg));
	std::cout << "i send to the server [" << sendmsg << "]" << std::endl;
	memset(toto, 0, 42);
	std::size_t res = sock->receive(toto, 42);
	if (res > 0)
	{
		std::cout << "server send to me [" << toto << "]" << std::endl;
	}
}

void testserver()
{
	ISocketTCP *sock = new SocketTCP();
	ISocketTCP *client;
	char sendmsg[] = "i am the server !";
	char toto[42];

	sock->init();
	sock->bind(PORT, IPADRESS);
	sock->listen(10);
	client = NULL;
	client = sock->accept();
	memset(toto, 0, 42);
	std::size_t res = 0;
	if ((res = client->receive(toto, 42)))
	{
		if (res > 0)
		{
			std::cout << "server recieve [" << toto << "]" << std::endl;
			//sock->send(sendmsg, strlen(sendmsg));
		}
	}
}

int	main()
{
	// BUG SERVER PARTIE
	// RECIEVE FAILED !!!!
	//testclient();
	testserver();

#ifdef __linux__
	sleep(4);
#elif _WIN32
	Sleep(10000);
#endif
}