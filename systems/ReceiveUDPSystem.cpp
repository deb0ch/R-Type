#include "ReceiveUDPSystem.hh"
#include "NetworkBuffer.hh"
#include "INetworkRelay.hh"
#include "Remote.hh"
#include "Room.hh"

ReceiveUDPSystem::ReceiveUDPSystem() : ASystem("ReceiveUDPSystem", 1)
{}

ReceiveUDPSystem::~ReceiveUDPSystem()
{}

bool ReceiveUDPSystem::canProcess(Entity *)
{
  return (false);
}

void ReceiveUDPSystem::processEntity(Entity *, const float)
{}

void			ReceiveUDPSystem::beforeProcess()
{
  auto			network_buffer =
    this->_world->getSharedObject< std::vector<IBuffer *> >("NetworkUDPBuffer");
  INetworkRelay		*network = this->_world->getSharedObject< INetworkRelay >("NetworkRelay");
  Room			*room;

  room = network->getRoom("toto");
  std::vector<Remote *> &remotes = room->getRemotes();
  std::for_each(remotes.begin(), remotes.end(),
		[&network_buffer] (Remote *remote) -> void
		{
		  SafeFifo<IBuffer *> &recv_fifo = remote->getRecvBufferUDP();

		  while (!recv_fifo.isEmpty())
		    network_buffer->push_back(recv_fifo.getNextPop());
		});
}
