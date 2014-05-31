#ifndef FIREALWAYSCOMPONENT_H_
# define FIREALWAYSCOMPONENT_H_

# include	"ACopyableComponent.hpp"

class		FireAlwaysComponent : public ACopyableComponent<FireAlwaysComponent>
{
public:
		FireAlwaysComponent();
  virtual	~FireAlwaysComponent();

  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;
};

#endif /* !FIREALWAYSCOMPONENT_H_ */
