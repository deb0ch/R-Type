#ifndef AUTODESTRUCTCOMPONENT_H_
# define AUTODESTRUCTCOMPONENT_H_

# include "ACopyableComponent.hpp"

class AutoDestructComponent : public ACopyableComponent<AutoDestructComponent>
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
  virtual void serialize(IBuffer &) const;
  virtual void unserialize(IBuffer &);
};

#endif /* !AUTODESTRUCTCOMPONENT_H_ */
