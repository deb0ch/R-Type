#ifndef IEVENT_H_
# define IEVENT_H_

# include <string>
# include "IEvent.hh"

class IEvent
{
public:
  virtual ~IEvent()
  {}
  virtual const std::string &getType() const = 0;
};

#endif /* !IEVENT_H_ */
