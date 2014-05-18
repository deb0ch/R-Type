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
      std::vector<Remote *> c = a.getRemotes("default");
      std::for_each(c.begin(), c.end(), [&a] (Remote *remote) -> void {
      	  SafeFifo<IBuffer *> &buffers = remote->getRecvBufferUDP();
      	  std::string tmp;
      	  while (!buffers.isEmpty())
      	    {
      	      IBuffer *buffer = buffers.getNextPop();
      	      *buffer >> tmp;
      	      std::cout << "AMEN: " << tmp << std::endl;
      	      a.disposeUDPBuffer(buffer);
      	      buffer = a.getUDPBuffer();
      	      *buffer << "mais lol";
      	      remote->sendUDP(buffer);
      	    }
      	  remote->unlock();
      	});
      usleep(5000);
    }
  return (0);
}
