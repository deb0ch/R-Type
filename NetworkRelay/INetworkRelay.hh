#ifndef INETWORKRELAY_H_
# define INETWORKRELAY_H_

# include <vector>
# include "IBuffer.hh"
# include "Any.hpp"

class Remote;

class INetworkRelay
{
public:
  virtual				~INetworkRelay()
  {}

  virtual void				start() = 0;
  virtual void				start(Any) = 0;
  virtual std::vector<Remote *>		getRemotes(const std::string &room_name) = 0;
  virtual void				sendBroadcastUDP(const std::string &room_name,
							 IBuffer &buffer) = 0;
  virtual void				sendBroadcastTCP(const std::string &room_name,
							 IBuffer &buffer) = 0;
  virtual IBuffer			*getTCPBuffer() = 0;
  virtual IBuffer			*getUDPBuffer() = 0;
  virtual Remote			*getRemote(unsigned int) = 0;
  virtual Remote			*getRemote(const std::string &ip, const int port) = 0;
  virtual void				disposeUDPBuffer(IBuffer *) = 0;
  virtual void				disposeTCPBuffer(IBuffer *) = 0;
  virtual bool				isReady() const = 0;
protected:
};

#endif /* !INETWORKRELAY_H_ */
