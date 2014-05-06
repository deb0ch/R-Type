#ifndef PLAYERMOVEMENTSYSTEM_H_
# define PLAYERMOVEMENTSYSTEM_H_

# include <map>
# include "ASystem.hh"
# include "SFML/Window/Keyboard.hpp"

class PlayerMovementSystem : public ASystem
{
public:
  PlayerMovementSystem();
  virtual ~PlayerMovementSystem();
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *, const float);
protected:
  static const std::map<std::string, std::pair<int, int> > KeyMovement;
};

#endif /* !PLAYERMOVEMENTSYSTEM_H_ */
