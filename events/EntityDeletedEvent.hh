#ifndef ADDENTITYTODELETE_H_
# define ADDENTITYTODELETE_H_

# include "AEvent.hh"
# include "Entity.hh"

class EntityDeletedEvent : public AEvent
{
public:
  EntityDeletedEvent() = delete;
  EntityDeletedEvent(Entity *entity, bool forced = false);
  virtual ~EntityDeletedEvent();

public:
  Entity *getEntity(void);
  const Entity *getEntity(void) const;
  bool	isForced() const;

protected:
  Entity *_entity;
  bool	_forced;

};

#endif /* !ADDENTITYTODELETE_H_ */
