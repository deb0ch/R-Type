#ifndef AUTODESTRUCTCOMPONENT_H_
# define AUTODESTRUCTCOMPONENT_H_

# include "AComponent.hpp"

class AutoDestructComponent : public AComponent<AutoDestructComponent>
{
protected:
  unsigned long _delay;
  unsigned long _tick;

public:
  AutoDestructComponent(unsigned long delay = 3);
  virtual	~AutoDestructComponent();

  unsigned long getDelay() const;
  unsigned long getTick() const;
  void setDelay(unsigned long delay);
  void setTick(unsigned long tick);
};

#endif /* !AUTODESTRUCTCOMPONENT_H_ */
