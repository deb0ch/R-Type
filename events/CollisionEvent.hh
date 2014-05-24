#ifndef COLLISIONEVENT_H_
# define COLLISIONEVENT_H_

# include	"AEvent.hh"

# include	"Entity.hh"

class CollisionEvent : public AEvent
{
public:
  CollisionEvent(Entity* entity1, Entity* entity2);
  virtual	~CollisionEvent();
  Entity*	getEntity1() const;
  Entity*	getEntity2() const;

protected:
  Entity	*entity1;
  Entity	*entity2;
};

#endif /* !COLLISIONEVENT_H_ */
