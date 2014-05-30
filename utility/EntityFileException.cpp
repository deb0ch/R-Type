#include <sstream>
#include "EntityFileException.hh"

//----- ----- Constructors ----- ----- //
EntityFileException::EntityFileException(std::string message, unsigned int lineno)
{
  this->_message = message;
  this->_lineno = lineno;
  this->_filename = "Unkwown filename";
}

//----- ----- Destructor ----- ----- //
EntityFileException::~EntityFileException()
{}

//----- ----- Operators ----- ----- //

//----- ----- Getters ----- ----- //
const char*	EntityFileException::what() const noexcept
{
  std::stringstream	res;

  res << "===== EntityFileException =====" << std::endl;
  if (this->_filename != "")
    {
      res << "Where ?\tDuring parsing of [" << this->_filename << "]";
      if (this->_lineno > 0)
	res << "(Line #" << this->_lineno << ")";
      res << std::endl;
    }
  if (this->_component != "")
    res << "When ?\tWhen deserializing component " << this->_component << std::endl;
  res << "What ?\t" << this->_message << std::endl;

  return (res.str().c_str());
}

//----- ----- Setters ----- ----- //
void		EntityFileException::setFilename(const std::string &filename)
{
  this->_filename = filename;
}

void		EntityFileException::setComponent(const std::string &component)
{
  this->_component = component;
}

void		EntityFileException::setLineNo(unsigned int lineno)
{
  this->_lineno = lineno;
}
