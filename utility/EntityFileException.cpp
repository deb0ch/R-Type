#include "EntityFileException.hh"

//----- ----- Constructors ----- ----- //
EntityFileException::EntityFileException(std::string message, unsigned int lineno)
{
  this->_message = message;
  this->_lineno = lineno;
}

//----- ----- Destructor ----- ----- //
EntityFileException::~EntityFileException()
{}

//----- ----- Operators ----- ----- //

//----- ----- Getters ----- ----- //
const char*	EntityFileException::what() const noexcept
{
  return (std::string("EntityFileException: [Line #" + std::to_string(this->_lineno) + "] " + this->_message ).c_str());
}

//----- ----- Setters ----- ----- //
