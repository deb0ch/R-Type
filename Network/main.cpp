#include <list>
#include <iostream>
#include <stdio.h>
#include <string.h>

#ifdef __linux__
#include <unistd.h>
#include <stdlib.h>
#elif _WIN32
#include <Windows.h>
#endif

#include "NetworkBuffer.hh"
#include "Select.hh"
#include "Socket.hh"

#define IPADRESS_CLIENT "10.41.177.3"
#define IPADRESS_SERVER "10.41.178.237"
#define PORT 6667

void testclient()
{
	ISocketTCP *sock = new SocketTCP();
	NetworkBuffer test;
	char sendmsg[] = "i am the client !";
	sock->init();
	sock->connect(IPADRESS_CLIENT, PORT);
	std::string line;
	while (std::getline(std::cin, line))
	{
		test << line;
		sock->send(test);
	}
}

void testserver()
{
	ISocketTCP *sock = new SocketTCP();
	ISocketTCP *client;
	char sendmsg[] = "i am the server !";
	char toto[42];

	sock->init();
	sock->bind(PORT, IPADRESS_SERVER);
	sock->listen(10);
	client = NULL;
	client = sock->accept();
	memset(toto, 0, 42);
	std::size_t res = 0;
	std::string line;
	NetworkBuffer test;
	while (sock->receive(test))
	{
		std::cout << test.getBuffer() << std::endl;
	}
}

void testrecept()
{
	ISocketUDP *sock = new SocketUDP();
	std::string ipaddress;
	int port;
	int res;
	NetworkBuffer test;

	sock->init();
	sock->bind(PORT, IPADRESS_CLIENT);
	res = 1;
	while (sock->receive(test, ipaddress, port))
	{
		std::cout << ipaddress << ":" << port << " send " << test.getBuffer() << std::endl;
	}
}

void testsend()
{
	ISocketUDP *sock = new SocketUDP();
	std::string line;
	int res;
	NetworkBuffer test;

	sock->init();
	res = 1;
	while (std::getline(std::cin, line))
	{
		test << line;
		res = sock->send(test, IPADRESS_CLIENT, PORT);
	}
}

void	selecttest()
{
  std::list<ISocket *>	l;
  Select	s(2);

  l.push_back(new SocketUDP());
  l.push_back(new SocketUDP());
  l.push_back(new SocketUDP());
  l.push_back(new SocketUDP());
  while (42)
    {
      s.initReads(l);
      s.doSelect();
      if (s.issetReads(l.front()->getHandle()))
	std::cout << "Yeah baby!" << std::endl;
    }
}

int	main()
{
	// TCP
	//testclient();
	//testserver();

	// UDP
	testrecept();
	//testsend();

	// SELECT
	//selecttest();
#ifdef __linux__
	sleep(4);
#elif _WIN32
	Sleep(10000);
#endif
}
