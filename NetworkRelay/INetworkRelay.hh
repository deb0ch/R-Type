#ifndef INETWORKRELAY_H_
# define INETWORKRELAY_H_

# include <vector>
# include "IBuffer.hh"
# include "Any.hpp"

class Remote;
class Room;

class INetworkRelay
{
public:
  enum TCPType
    {
      CHANGE_ROOM_QUERY,
      CHANGE_ROOM_QUERY_YES,
      CHANGE_ROOM_QUERY_NON
    };

public:
  virtual				~INetworkRelay()
  {}

  virtual bool				start() = 0;
  virtual void				start(Any) = 0;
  virtual Room				*getRoom(const std::string &room_name) = 0;
  virtual IBuffer			*getTCPBuffer() = 0;
  virtual IBuffer			*getUDPBuffer() = 0;
  virtual Remote			*getRemote(unsigned int) = 0;
  virtual Remote			*getRemote(const std::string &ip, const int port) = 0;
  virtual void				disposeUDPBuffer(IBuffer *) = 0;
  virtual void				disposeTCPBuffer(IBuffer *) = 0;
protected:
};

#endif /* !INETWORKRELAY_H_ */
