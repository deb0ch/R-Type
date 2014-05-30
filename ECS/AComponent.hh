#ifndef ACOMPONENT_H_
# define ACOMPONENT_H_

# include	<algorithm>
# include	<string>
# include	<iostream>
# include	<fstream>
# include	<regex>

# include	"IComponent.hh"
# include	"Hash.hh"
#include	"EntityFileException.hh"

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
    std::string		line;
    while (std::getline(input, line))
      {
	line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

	if (std::regex_match(line, std::regex("!COMPONENT")))
	    return ;
	else
	  this->deserializeFromFileSpecial(line, input);
      }
  }

  virtual void		deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
  {
    (void)lastline;
    (void)input;
    throw "deserializeFromFileSpecial() not defined for " + this->_type;
  }

  virtual void		serializeFromFile(std::ofstream &output, unsigned char indent) const
  {
    (void)output;
    (void)indent;
    throw "serializeFromFile not defined for " + this->_type;
  }
};

#endif /* !ACOMPONENT_H_ */
