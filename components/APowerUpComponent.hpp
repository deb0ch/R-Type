#ifndef APOWERUPCOMPONENT_H_
# define APOWERUPCOMPONENT_H_

# include <string>
# include "ACopyableComponent.hpp"
# include "EntitySpawnerComponent.hh"

class APowerUpComponent : public ASerializableComponent
{
public:
  APowerUpComponent(const std::string &name) : ASerializableComponent(name)
  {}
  virtual	~APowerUpComponent()
  {}

  virtual void	upgrade(World *, Entity *target) = 0;

  void		serialize(IBuffer &) const
  {}
  void		unserialize(IBuffer &)
  {}


};

#endif /* !APOWERUPCOMPONENT_H_ */
