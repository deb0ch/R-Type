#ifndef ADDENTITYTODELETE_H_
# define ADDENTITYTODELETE_H_

# include "AEvent.hh"
# include "Entity.hh"

class EntityDeletedEvent : public AEvent
{
public:
  EntityDeletedEvent() = delete;
  EntityDeletedEvent(Entity *entity);
  virtual ~EntityDeletedEvent();

public:
  Entity *getEntity(void);

protected:
  Entity *_entity;

};

#endif /* !ADDENTITYTODELETE_H_ */
