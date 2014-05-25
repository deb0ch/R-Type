#ifndef DISCONNECTPLAYEREVENT_H_
# define DISCONNECTPLAYEREVENT_H_

# include "AEvent.hh"

class DisconnectPlayerEvent : public AEvent
{
public:
  DisconnectPlayerEvent(unsigned int hash);
  virtual ~DisconnectPlayerEvent();
  unsigned int getRemoteId() const;
protected:
  unsigned int _hash;
};

#endif /* !DISCONNECTPLAYEREVENT_H_ */
