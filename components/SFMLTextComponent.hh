#ifndef SFMLTEXTCOMPONENT_H_
# define SFMLTEXTCOMPONENT_H_

# include "ACopyableComponent.hpp"

class SFMLTextComponent : public ACopyableComponent<SFMLTextComponent>
{

public:
  SFMLTextComponent(const std::string &text = "Nothing to write");
  virtual	~SFMLTextComponent();
  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);
  const std::string &getText() const;
  void setText(const std::string &text);

  virtual void	deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &);
  virtual void	serializeFromFile(std::ofstream &output, unsigned char indent) const;

protected:
  std::string	_text;

};

#endif /* !SFMLTEXTCOMPONENT_H_ */
