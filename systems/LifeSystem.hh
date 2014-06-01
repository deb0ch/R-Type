#ifndef LIFESYSTEM_H_
# define LIFESYSTEM_H_

# include		"ASystem.hh"

class			LifeSystem : public ASystem
{
protected:
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *, const float);

public:
  LifeSystem();
  virtual ~LifeSystem();
  void	collision_event(IEvent *);
  void	delete_entity(IEvent *);
};

#endif /* !LIFESYSTEM_H_ */
