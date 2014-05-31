#ifndef SFMLTEXTCOMPONENT_H_
# define SFMLTEXTCOMPONENT_H_

# include "ACopyableComponent.hpp"

class SFMLTextComponent : public ACopyableComponent<SFMLTextComponent>
{

public:
  SFMLTextComponent(const std::string &text = "");
  virtual	~SFMLTextComponent();
  virtual void	serialize(IBuffer &buffer) const;
  virtual void	unserialize(IBuffer &buffer);
  const std::string &getText() const;

protected:
  std::string	_text;

};

#endif /* !SFMLTEXTCOMPONENT_H_ */
