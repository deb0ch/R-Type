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
  std::vector<Remote *> tmp_remotes;

  // Get a remote to start ping pong talking
  do
    {
      sleep(1);
      tmp_remotes = a.getRemotes("default");
    } while (tmp_remotes.empty());
  IBuffer *tmp_buffer = a.getTCPBuffer();
  *tmp_buffer << "coucou";
  Remote *tmp_remote = tmp_remotes.front();
  tmp_remote->sendTCP(tmp_buffer);
  tmp_remote->unlock();

  while (1)
    {
      std::vector<Remote *> c = a.getRemotes("default");
      std::for_each(c.begin(), c.end(), [&a] (Remote *remote) -> void {
	  SafeFifo<IBuffer *> &buffers = remote->getRecvBufferTCP();
	  std::string tmp;
	  while (!buffers.isEmpty())
	    {
	      IBuffer *buffer = buffers.getNextPop();
	      *buffer >> tmp;
	      std::cout << "AMEN: " << tmp << std::endl;
	      a.disposeUDPBuffer(buffer);
	      buffer = a.getTCPBuffer();
	      *buffer << "mais lol";
	      remote->sendTCP(buffer);
	    }
	  remote->unlock();
      	});
      usleep(5000);
    }
  return (0);
}
