#ifndef ACTIONMOVEMENTSYSTEM_H_
# define ACTIONMOVEMENTSYSTEM_H_

# include <map>
# include "ASystem.hh"
# include "SFML/Window/Keyboard.hpp"

class ActionMovementSystem : public ASystem
{
public:
	ActionMovementSystem();
	virtual ~ActionMovementSystem();
  virtual bool canProcess(Entity *);
  virtual void processEntity(Entity *, const float);
protected:
  static const std::map<std::string, std::pair<int, int> > KeyMovement;
};

#endif /* !PLAYERMOVEMENTSYSTEM_H_ */
