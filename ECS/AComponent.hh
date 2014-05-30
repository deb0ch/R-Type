#ifndef ACOMPONENT_H_
# define ACOMPONENT_H_

# include	<string>
# include	"IComponent.hh"


# include <iostream>
# include "Hash.hh"

class		AComponent : public IComponent
{
protected:
  std::string	_type;

public:
  AComponent() = delete;
  AComponent(const std::string &type)
  {
    this->_type = type;
  }
  virtual	~AComponent()
  {}

  virtual const std::string	&getType() const
  {
    return (this->_type);
  }

  virtual void		deserializeFromFile(std::ifstream &input)
  {
    (void)input;
  }

  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const
  {
    (void)output;
    (void)indent;
    throw "Not defined for  " + this->_type;
  }
};

#endif /* !ACOMPONENT_H_ */
