#ifndef APOWERUPCOMPONENT_H_
# define APOWERUPCOMPONENT_H_

# include <string>
# include "ACopyableComponent.hpp"
# include "EntitySpawnerComponent.hh"

class APowerUpComponent : public AComponent
{
public:
  APowerUpComponent() : AComponent("APowerUpComponent")
  {}
  virtual	~APowerUpComponent()
  {}

  virtual void	upgrade(World *, Entity *target) = 0;

  void		serialize(IBuffer &) const
  {}
  void		unserialize(IBuffer &)
  {}

protected:
  std::string _newWeapon;
  float _newdelay;

};

#endif /* !APOWERUPCOMPONENT_H_ */
