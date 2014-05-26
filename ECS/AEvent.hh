#ifndef AEVENT_H_
# define AEVENT_H_

# include "IEvent.hh"

class AEvent : public IEvent
{
public:
  AEvent(const std::string &type);
  virtual ~AEvent();
  virtual const std::string &getType() const;
private:
  AEvent();
protected:
  std::string _type;
};

#endif /* !AEVENT_H_ */
