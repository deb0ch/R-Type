#ifndef AUTODESTRUCTCOMPONENT_H_
# define AUTODESTRUCTCOMPONENT_H_

# include "ACopyableComponent.hpp"

class AutoDestructComponent : public ACopyableComponent<AutoDestructComponent>
{
protected:
  float		_delay;
  float		_tick;

public:
  AutoDestructComponent(float delay = 0.05f);
  virtual	~AutoDestructComponent();

  float getDelay() const;
  float getTick() const;
  void setDelay(float delay);
  void setTick(float tick);
  virtual void serialize(IBuffer &) const;
  virtual void unserialize(IBuffer &);

  void	serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !AUTODESTRUCTCOMPONENT_H_ */
