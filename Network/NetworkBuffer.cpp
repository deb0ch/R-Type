#include "NetworkBuffer.hh"

NetworkBuffer::NetworkBuffer()
{
  this->_buffer_size = 0;
  this->_current_pos = 0;
}

NetworkBuffer::~NetworkBuffer()
{}

bool		NetworkBuffer::end() const
{
  if (this->_current_pos >= this->_buffer_size)
    return (true);
  return (false);
}

void		NetworkBuffer::rewind()
{
  this->_current_pos = 0;
}

IBuffer		&NetworkBuffer::operator<<(const int &value)
{
  this->serialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator<<(const unsigned int &value)
{
  this->serialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator<<(const float &value)
{
  this->serialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator<<(const std::string &value)
{
  this->serialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator<<(const std::size_t &value)
{
  this->serialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator<<(const char &value)
{
  this->serialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator>>(int &value)
{
  this->unserialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator>>(unsigned int &value)
{
  this->unserialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator>>(float &value)
{
  this->unserialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator>>(std::string &value)
{
  this->unserialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator>>(std::size_t &value)
{
  this->unserialize(value);
  return (*this);
}

IBuffer		&NetworkBuffer::operator>>(char &value)
{
  this->unserialize(value);
  return (*this);
}

template <>
void		NetworkBuffer::serialize<std::string>(const std::string &element)
{
  this->serialize<unsigned int>(element.length());
  if (this->_buffer_size + element.length() > bufferMaxSize)
    {
      std::cerr << "Invalid size" << std::endl; // raise exception
      return ;
    }
  for (auto it = element.begin(); it != element.end(); ++it)
    {
      this->_buffer[this->_buffer_size] = *it;
      ++this->_buffer_size;
    }
}

template <>
void		NetworkBuffer::unserialize<std::string>(std::string &element)
{
  unsigned int	size;

  element = "";
  this->unserialize<unsigned int>(size);
  if (this->_buffer_size - this->_current_pos < size)
    {
      std::cout << "Not enough space" << std::endl; // raise exception
      return ;
    }
  for (unsigned int i = 0; i < size; ++i)
    {
      element += this->_buffer[this->_current_pos];
      ++this->_current_pos;
    }
}