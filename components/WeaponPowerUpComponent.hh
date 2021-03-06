#ifndef WEAPONPOWERUPCOMPONENT_H_
# define WEAPONPOWERUPCOMPONENT_H_

# include <string>
# include "ACopyableComponent.hpp"
# include "EntitySpawnerComponent.hh"
# include "APowerUpComponent.hpp"

class WeaponPowerUpComponent : public APowerUpComponent
{
public:
  WeaponPowerUpComponent(const std::string weapon = "", float delay = 0.15f);
  virtual	~WeaponPowerUpComponent();

  virtual void	upgrade(World *, Entity *);

  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

  virtual ASerializableComponent	*cloneSerializable() const;

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input,
					   unsigned int &lineno);

protected:
  std::string _newWeapon;
  float _newdelay;
};

#endif /* !WEAPONPOWERUPCOMPONENT_H_ */
