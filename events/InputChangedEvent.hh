#ifndef INPUTCHANGEDEVENT_H_
# define INPUTCHANGEDEVENT_H_

# include "AEvent.hh"
# include "Entity.hh"

class InputChangedEvent : public AEvent
{
public:
  InputChangedEvent(Entity *e, const std::string &input);
  virtual ~InputChangedEvent();
  const Entity *getEntity() const;
  Entity *getEntity();
  const std::string &getInput() const;
protected:
  Entity *_entity;
  const std::string &_input;
};

#endif /* !INPUTCHANGEDEVENT_H_ */
