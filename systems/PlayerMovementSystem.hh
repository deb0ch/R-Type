#ifndef PLAYERMOVEMENTSYSTEM_H_
# define PLAYERMOVEMENTSYSTEM_H_

# include "ASystem.hh"

class PlayerMovementSystem : public ASystem
{
public:
  PlayerMovementSystem();
  virtual ~PlayerMovementSystem();
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *);
protected:

};

#endif /* !PLAYERMOVEMENTSYSTEM_H_ */
