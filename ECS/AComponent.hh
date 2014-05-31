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

  virtual void		deserializeFromFile(std::ifstream &input, unsigned int &lineno)
  {
    std::string		line;
    while (std::getline(input, line))
      {
	++lineno;
	line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

	if (std::regex_match(line, std::regex("!COMPONENT")))
	    return ;
	else
	  {
	    try {
	      this->deserializeFromFileSpecial(line, input, lineno);
	    }
	    catch (EntityFileException &efe)
	      {
		efe.setComponent(this->_type);
		efe.setLineNo(lineno);
		throw;
	      }
	    catch (const std::invalid_argument &ia)
	      {
		EntityFileException efe("Bad argument : expecting number", lineno);
		efe.setComponent(this->_type);
		throw efe;
	      }
	  }
      }
  }

  virtual void		deserializeFromFileSpecial(const std::string &, std::ifstream &, unsigned int&)
  {
    throw "deserializeFromFileSpecial() not defined for " + this->_type;
  }

  virtual void		serializeFromFile(std::ofstream &, unsigned char) const
  {
    throw "serializeFromFile() not defined for " + this->_type;
  }
};

#endif /* !ACOMPONENT_H_ */
