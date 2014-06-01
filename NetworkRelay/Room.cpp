#include <algorithm>
#include "NewPlayerEvent.hh"
#include "DisconnectPlayerEvent.hh"
#include "Room.hh"

Room::Room()
  : _remotes(), _mutex()
{
}

Room::~Room(){}

void				Room::lock() {this->_mutex.lock();}
void				Room::unlock() {this->_mutex.unlock();}
bool				Room::trylock() {return (this->_mutex.trylock());}
std::vector<Remote *>		&Room::getRemotes() {return (this->_remotes);}
const std::vector<Remote *>	&Room::getRemotes() const {return (this->_remotes);}

std::vector<Remote *>		&Room::getPendingDisonnectRemotes()
{
  return (this->_pending_disconnect_remotes);
}

void				Room::disconnectRemote(Remote *remote)
{
  if (std::find(this->_pending_disconnect_remotes.begin(),
		this->_pending_disconnect_remotes.end(), remote) ==
      this->_pending_disconnect_remotes.end())
    {
      this->_pending_disconnect_remotes.push_back(remote);
    }
}

void				Room::removeRemote(Remote *remote)
{
  auto it = std::find(this->_remotes.begin(), this->_remotes.end(), remote);

  if (it == this->_remotes.end())
    return ;
  this->_remotes.erase(it);
}

void				Room::sendBroadcastUDP(INetworkRelay &network,
						       IBuffer *buffer, bool make_copy)
{
  auto				it = this->_remotes.begin();
  Remote			*tmp;
  IBuffer			*tmp_buffer;

  while (it != this->_remotes.end())
    {
      tmp = *it;
      ++it;
      if (it != this->_remotes.end() || make_copy == true)
	{
	  tmp_buffer = network.getUDPBuffer();
	  *tmp_buffer = *buffer;
	}
      else
	tmp_buffer = buffer;
      tmp->sendUDP(tmp_buffer);
    }
  if (this->_remotes.empty())
    network.disposeUDPBuffer(buffer);
}

void				Room::sendBroadcastTCP(INetworkRelay &network,
						       IBuffer *buffer, bool make_copy)
{
  auto				it = this->_remotes.begin();
  Remote			*tmp;
  IBuffer			*tmp_buffer;

  while (it != this->_remotes.end())
    {
      tmp = *it;
      ++it;
      if (it != this->_remotes.end() || make_copy == true)
	{
	  tmp_buffer = network.getTCPBuffer();
	  *tmp_buffer = *buffer;
	}
      else
	tmp_buffer = buffer;
      tmp->sendTCP(tmp_buffer);
    }
  if (this->_remotes.empty())
    network.disposeTCPBuffer(buffer);
}
