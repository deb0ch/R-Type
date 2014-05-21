#ifndef ROOM_H_
# define ROOM_H_

# include <vector>
# include "Remote.hh"
# include "Mutex.hh"

class Room
{
public:
  Room();
  virtual			~Room();
  void				lock();
  void				unlock();
  bool				trylock();
  std::vector<Remote *>		&getRemotes();
  const std::vector<Remote *>	&getRemotes() const;
  void				disconnectRemote(Remote *remote);
  std::vector<Remote *>		&getPendingDisonnectRemotes();
  void				removeRemote(Remote *remote);
  void				sendBroadcastUDP(INetworkRelay &, IBuffer *buffer, bool make_copy = false);
  void				sendBroadcastTCP(INetworkRelay &, IBuffer *buffer, bool make_copy = false);

private:
  Room(const Room &) = delete;
  Room &operator=(const Room &) = delete;
protected:
  std::vector<Remote *>	_remotes;
  std::vector<Remote *>	_pending_disconnect_remotes;
  Mutex			_mutex;
};

#endif /* !ROOM_H_ */
