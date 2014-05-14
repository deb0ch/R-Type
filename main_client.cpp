#include "ClientRelay.hh"
#include "Threads/Threads.hh"
#include "TCPException.hh"

int	main()
{
  Thread<ClientRelay> thread;
  Any b;

  ClientRelay a("127.0.0.1", 6667);
  thread.start(&a, &ClientRelay::start, b);
  while (!a.isReady());
  std::cout << "toto" << std::endl;
  return (0);
}
