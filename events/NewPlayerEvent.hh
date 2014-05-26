#ifndef NEWPLAYEREVENT_H_
# define NEWPLAYEREVENT_H_

# include "AEvent.hh"

class NewPlayerEvent : public AEvent
{
public:
  NewPlayerEvent(unsigned int hash);
  virtual ~NewPlayerEvent();
  unsigned int getRemoteId() const;
protected:
  unsigned int _hash;
};

#endif /* !NEWPLAYEREVENT_H_ */
