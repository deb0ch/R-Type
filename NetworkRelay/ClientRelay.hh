#ifndef CLIENTRELAY_H_
# define CLIENTRELAY_H_

# include "Socket.hh"
# include "Select.hh"
# include "NetworkInitializer.hh"
# include "INetworkRelay.hh"
# include "Remote.hh"

class ClientRelay : public INetworkRelay
{
public:
  ClientRelay(const std::string &ip, const int port = 42);
  virtual				~ClientRelay();
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
  virtual bool				isReady() const;

private:
  void					waitForEvent();
  void					udpConnect();

protected:
  NetworkInitializer			_network_initializer;
  SocketUDP				_socket_udp;
  Select				_select;
  Remote				*_remote;
};

#endif /* !CLIENTRELAY_H_ */
