#include	<iostream>

#include	"ServerRelay.hh"

int		main()
{
  ServerRelay *server = new ServerRelay(6667, 42);
  server->start();

  return (0);
}
