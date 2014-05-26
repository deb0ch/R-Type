#include "BufferException.hh"

BufferException::BufferException(IBuffer *buffer, const std::string &error_str) throw() : std::exception()
{
  this->_str = (std::string("BufferException: ") + error_str
		+ "\nPosition = " + std::to_string(buffer->getPosition())
		+ " Length = " + std::to_string(buffer->getLength())
		+ " Offset = " + std::to_string(buffer->getOffset())
		+ " MaxLength = " + std::to_string(buffer->getMaxSize())
		+ " RemainingLength = " + std::to_string(buffer->getRemainingLength())).c_str();
}

BufferException::~BufferException() throw()
{}

const char *BufferException::what() const throw()
{
  return (this->_str);
}
