#include "AEvent.hh"

AEvent::AEvent(const std::string &type)
{
  this->_type = type;
}

AEvent::~AEvent()
{}

const std::string &AEvent::getType() const
{
  return (this->_type);
}
