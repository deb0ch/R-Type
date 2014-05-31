#ifndef __MOVEMENTFORWARDCOMPONENT_H_
# define __MOVEMENTFORWARDCOMPONENT_H_

# include	"Entity.hh"
# include	"World.hh"
# include	"ACopyableComponent.hpp"

class		MoveForwardComponent : public ACopyableComponent<MoveForwardComponent>
{
public:
  MoveForwardComponent(const std::string &dir1 = "", const std::string &dir2 = "");
  virtual	~MoveForwardComponent();

  const std::pair<std::string, std::string>	getDirection() const;

  virtual void	serialize(IBuffer &) const;
  virtual void	unserialize(IBuffer &);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
    std::string		_direction1;
  std::string		_direction2;
};

#endif /* !MOVEMENTFORWARDCOMPONENT_H_ */
