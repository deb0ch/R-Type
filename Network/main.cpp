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

#include "Select.hh"
#include "Socket.hh"

#define IPADRESS_CLIENT "10.41.177.15"
#define IPADRESS_SERVER "10.41.179.57"
#define PORT 6667

void testclient()
{
	ISocketTCP *sock = new SocketTCP();
	char sendmsg[] = "i am the client !";
	sock->init();
	sock->connect(IPADRESS_CLIENT, PORT);
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
	sock->bind(PORT, IPADRESS_SERVER);
	sock->listen(10);
	client = NULL;
	client = sock->accept();
	memset(toto, 0, 42);
	std::size_t res = 0;
	while ((res = client->receive(toto, 42)))
	{
		if (res > 0)
		{
			std::cout << "server recieve [" << toto << "]" << std::endl;
			//sock->send(sendmsg, strlen(sendmsg));
		}
	}
}

void testrecept()
{
	ISocketUDP *sock = new SocketUDP();
	char toto[42];
	std::string ipaddress;
	int port;
	int res;

	sock->init();
	sock->bind(PORT, IPADRESS_CLIENT);
	res = 1;
	while (res != 0)
	{
		memset(toto, 0, 42);
		res = sock->receive(toto, 42, ipaddress, port);
		std::cout << ipaddress << " send " << toto << std::endl;
	}
}

void testsend()
{
	ISocketUDP *sock = new SocketUDP();
	std::string line;
	int res;

	sock->init();
	res = 1;
	while (std::getline(std::cin, line))
	{
		res = sock->send(line.c_str(), 42, IPADRESS_CLIENT, PORT);
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
	//testrecept();
	//testsend();

	// SELECT
	selecttest();
#ifdef __linux__
	sleep(4);
#elif _WIN32
	Sleep(10000);
#endif
}
