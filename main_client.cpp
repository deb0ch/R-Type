#include <algorithm>
#include "ClientRelay.hh"
#include "Threads/Threads.hh"
#include "TCPException.hh"

int	main()
{
  Thread<ClientRelay> thread;
  Any b;
  Room *tmp_room;

  ClientRelay a("127.0.0.1", 6667);
  thread.start(&a, &ClientRelay::start, b);
  // Get a remote to start ping pong talking
  do
    {
      sleep(1);
      tmp_room = a.getRoom("default");
    } while (!tmp_room || tmp_room->getRemotes().empty());
  IBuffer *tmp_buffer = a.getTCPBuffer();
  *tmp_buffer << "coucou";
  tmp_room->sendBroadcastTCP(a, tmp_buffer);
  tmp_room->unlock();

  std::cout << "PROUT" << std::endl;
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
			  SafeFifo<IBuffer *> &buffers = remote->getRecvBufferTCP();
			  std::string tmp;
			  while (!buffers.isEmpty())
			    {
			      IBuffer *buffer = buffers.getNextPop();
			      *buffer >> tmp;
			      std::cout << "AMEN: " << tmp << std::endl;
			      a.disposeTCPBuffer(buffer);
			      buffer = a.getTCPBuffer();
			      *buffer << "mais lol";
			      remote->sendTCP(buffer);
			    }
			});
	  tmp_room->unlock();
	  usleep(5000);
	}
    }
  return (0);
}
