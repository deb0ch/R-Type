#ifndef SERVERRELAY_H_
# define SERVERRELAY_H_

# include <map>
# include "EventManager.hpp"
# include "INetworkRelay.hh"
# include "Select.hh"
# include "NetworkInitializer.hh"
# include "Remote.hh"

class ServerRelay : public INetworkRelay
{
private:
public:
  ServerRelay(int port = 4011, int nb_pending_connection = 42);
  virtual				~ServerRelay();
  virtual void				start();
  virtual void				start(Any);
  virtual std::vector<Remote *>		getRemotes(const std::string &room_name);
  virtual void				sendBroadcastUDP(const std::string &room_name,
							 IBuffer &buffer);
  virtual void				sendBroadcastTCP(const std::string &room_name,
							 IBuffer &buffer);
  virtual IBuffer			*getTCPBuffer();
  virtual IBuffer			*getUDPBuffer();
  virtual Remote			*getRemote(unsigned int);
  virtual Remote			*getRemote(const std::string &ip, const int port);
  virtual void				disposeUDPBuffer(IBuffer *);
  virtual void				disposeTCPBuffer(IBuffer *);
private:
  void					waitForEvent();
  void					addClient();
  unsigned int				generateHash();
  void					receiveUDP();
  void					removeRemote(Remote *remote);
  void					manageRemotes();
  void					udpConnect(Remote *remote);

protected:
  NetworkInitializer			_network_initializer;
  SocketTCP				_server_socket_tcp;
  SocketUDP				_server_socket_udp;
  Select				_select;
  std::vector<Remote *>			_remotes;
  // EventManager<> of some sort
};

#endif /* !SERVERRELAY_H_ */
