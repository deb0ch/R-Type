#ifndef LIFEPOWERUPCOMPONENT_H_
# define LIFEPOWERUPCOMPONENT_H_

# include <string>
# include "ACopyableComponent.hpp"
# include "EntitySpawnerComponent.hh"
# include "APowerUpComponent.hpp"

class LifePowerUpComponent : public APowerUpComponent
{
public:
  LifePowerUpComponent(unsigned int _nb_bonus = 1);
  virtual	~LifePowerUpComponent();

  virtual void	upgrade(World *, Entity *);

  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

  virtual IComponent	*clone() const;

protected:
  unsigned int	_nb_bonus;
};

#endif /* !LIFEPOWERUPCOMPONENT_H_ */
