#include <iostream>

#ifdef __linux__ 
#include "USocketTCP.hh"
#include <unistd.h>
#elif _WIN32
#include "WSocketTCP.hh"
#include <Windows.h>
#endif

void testclient()
{
	ISocketTCP *sock = new SocketTCP();
	char *sendmsg = "i am the client !";

	sock->init();
	sock->connect("127.0.0.1", 6667);
	char toto[42];
	std::size_t res = 0;
	sock->send(sendmsg, strlen(sendmsg));
	std::cout << "i send to the server [" << sendmsg << "]" << std::endl;
	memset(toto, 0, 42);
	res = sock->receive(toto, 42);
	if (res > 0)
	{
		std::cout << "server send to me [" << toto << "]" << std::endl;
	}
}

void testserver()
{
	ISocketTCP *sock = new SocketTCP();
	ISocketTCP *client;
	char *sendmsg = "i am the server !";
	char toto[42];

	sock->init();
	sock->bind(6667, "127.0.0.1");
	sock->listen(10);
	client = sock->accept();
	memset(toto, 0, 42);
	std::size_t res = 0;
	res = sock->receive(toto, 42);
	if (res > 0)
	{
		std::cout << "server recieve [" << toto << "]" << std::endl;
		//sock->send(sendmsg, strlen(sendmsg));
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
	Sleep(5000);
#endif
}