#ifndef ROOM_H_
# define ROOM_H_

# include <vector>
# include "Remote.hh"
# include "Mutex.hh"
# include "RunWorldServer.hh"

class Room
{
public:
  Room();
  virtual				~Room();
  virtual void				removeRemote(Remote *remote);
  virtual void				lock();
  virtual void				unlock();
  virtual bool				trylock();
  virtual std::vector<Remote *>		&getRemotes();
  virtual const std::vector<Remote *>	&getRemotes() const;
  virtual void				disconnectRemote(Remote *remote);
  virtual std::vector<Remote *>		&getPendingDisonnectRemotes();
  virtual void				sendBroadcastUDP(INetworkRelay &, IBuffer *buffer, bool make_copy = false);
  virtual void				sendBroadcastTCP(INetworkRelay &, IBuffer *buffer, bool make_copy = false);

private:
  Room(const Room &) = delete;
  Room &operator=(const Room &) = delete;

protected:
  std::vector<Remote *>	_remotes;
  std::vector<Remote *>	_pending_disconnect_remotes;
  Mutex			_mutex;

};

#endif /* !ROOM_H_ */
