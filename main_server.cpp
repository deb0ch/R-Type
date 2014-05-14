#include <algorithm>
#include "ServerRelay.hh"
#include "Threads/Threads.hh"
#include "TCPException.hh"

int	main()
{
  Thread<ServerRelay> thread;
  Any b;

  ServerRelay a(6667, 42);
  thread.start(&a, &ServerRelay::start, b);
  while (1)
    {
      // std::vector<Remote *> c = a.getRemotes("default");
      // std::for_each(c.begin(), c.end(), [] (Remote *remote) -> void {
      // 	  std::cout << remote->getPrivateHash() << std::endl;
      // 	  remote->unlock();
      // 	});
    }
  return (0);
}
