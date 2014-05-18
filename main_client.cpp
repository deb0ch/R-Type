#include <algorithm>
#include "ClientRelay.hh"
#include "Threads/Threads.hh"
#include "TCPException.hh"

int	main()
{
  Thread<ClientRelay> thread;
  Any b;

  ClientRelay a("127.0.0.1", 6667);
  thread.start(&a, &ClientRelay::start, b);
  while (!a.isReady())
    sleep(1);
  std::cout << "toto" << std::endl;
  IBuffer *tmp_buffer = a.getTCPBuffer();
  *tmp_buffer << "coucou";
  Remote *tmp_remote = a.getRemotes("").front();
  tmp_remote->sendUDP(tmp_buffer);
  tmp_remote->unlock();

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
      sleep(1);
    }
  return (0);
}
