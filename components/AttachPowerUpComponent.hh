#ifndef ATTACHPOWERUPCOMPONENT_H_
# define ATTACHPOWERUPCOMPONENT_H_

# include <string>
# include "ACopyableComponent.hpp"
# include "EntitySpawnerComponent.hh"
# include "APowerUpComponent.hpp"

class AttachPowerUpComponent : public APowerUpComponent
{
public:
  AttachPowerUpComponent(const std::string &entity_name = "");
  virtual	~AttachPowerUpComponent();

  virtual void	upgrade(World *, Entity *);

  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const;

  virtual ASerializableComponent	*cloneSerializable() const;

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input,
					   unsigned int &lineno);

protected:
  std::string _entity_name;
};

#endif /* !ATTACHPOWERUPCOMPONENT_H_ */
