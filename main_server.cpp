#include <algorithm>
#include "ServerRelay.hh"
#include "Threads/Threads.hh"
#include "TCPException.hh"

int	main()
{
  Thread<ServerRelay> thread;
  Any b;
  Room *tmp_room;

  ServerRelay a(6667, 42);
  thread.start(&a, &ServerRelay::start, b);
  while (1)
    {
      tmp_room = a.getRoom("default");
      if (tmp_room)
	{
	  std::for_each(tmp_room->getRemotes().begin(), tmp_room->getRemotes().end(),
			[&a] (Remote *remote) -> void
			{
			  if (!remote->isReady())
			    return ;
			  LockVector<IBuffer *> &buffers = remote->getRecvBufferTCP();
			  std::string tmp;
			  buffers.lock();
			  while (!buffers.empty())
			    {
			      IBuffer *buffer = buffers.front();
			      *buffer >> tmp;
			      std::cout << "AMEN: " << tmp << std::endl;
			      a.disposeTCPBuffer(buffer);
			      buffer = a.getTCPBuffer();
			      *buffer << "mais lol";
			      remote->sendTCP(buffer);
			      buffers.erase(buffers.begin());
			    }
			  buffers.unlock();
			});
	  tmp_room->unlock();
	}
      usleep(5000);
    }
  return (0);
}
