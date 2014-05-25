#include "NetworkBuffer.hh"

NetworkBuffer::NetworkBuffer(unsigned int size)
{
  this->_buffer_max_size = size;
  this->_buffer_size = 0;
  this->_current_pos = 0;
  this->_offset = 0;
  this->_buffer = new char[this->_buffer_max_size];
  this->_buffer_original = this->_buffer;
}

NetworkBuffer::~NetworkBuffer()
{
  delete[] (this->_buffer_original);
}

NetworkBuffer::NetworkBuffer(const IBuffer &buffer)
{
  const char	*cpy;

  std::cout << "COPY CONSTRUCT" << std::endl;
  this->_buffer_max_size = buffer.getMaxSize() + buffer.getOffset();
  this->_buffer = new char[this->_buffer_max_size];
  this->_buffer_original = this->_buffer;
  cpy = buffer.getBuffer() - buffer.getOffset();
  for (unsigned int i = 0; i < buffer.getLength() + buffer.getOffset(); ++i)
    {
      this->_buffer[i] = cpy[i];
    }
  this->_offset = buffer.getOffset();
  this->_buffer += this->_offset;
  this->_buffer_size = buffer.getLength();
  this->_current_pos = buffer.getPosition();
}

IBuffer		&NetworkBuffer::operator=(const IBuffer &buffer)
{
  const char	*cpy;

  if (this != &buffer)
    {
      this->_buffer_max_size = buffer.getMaxSize() + buffer.getOffset();
      this->_buffer = new char[this->_buffer_max_size];
      this->_buffer_original = this->_buffer;
      cpy = buffer.getBuffer() - buffer.getOffset();
      for (unsigned int i = 0; i < buffer.getLength() + buffer.getOffset(); ++i)
	{
	  this->_buffer[i] = cpy[i];
	}
      this->_offset = buffer.getOffset();
      this->_buffer += this->_offset;
      this->_buffer_size = buffer.getLength();
      this->_current_pos = buffer.getPosition();
    }
  return (*this);
}

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

void		NetworkBuffer::reset()
{
  this->_current_pos = 0;
  this->_buffer = this->_buffer_original;
  this->_offset = 0;
  this->_buffer_size = 0;
}

const char		*NetworkBuffer::getBuffer() const
{
  return (this->_buffer);
}

char			*NetworkBuffer::getBuffer()
{
  return (this->_buffer);
}

unsigned int		NetworkBuffer::getLength() const
{
  return (this->_buffer_size);
}

void			NetworkBuffer::setLength(unsigned int lenght)
{
  this->_buffer_size = lenght;
}

unsigned int		NetworkBuffer::getMaxSize() const
{
  return (this->_buffer_max_size);
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

IBuffer		&NetworkBuffer::operator<<(const unsigned long &value)
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

IBuffer		&NetworkBuffer::operator>>(unsigned long &value)
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

IBuffer		&NetworkBuffer::operator>>(char &value)
{
  this->unserialize(value);
  return (*this);
}

unsigned int	NetworkBuffer::getPosition() const
{
  return (this->_current_pos);
}

void		NetworkBuffer::setPosition(unsigned int pos)
{
  this->_current_pos = pos;
  if (this->_buffer_size < this->_current_pos)
    this->_buffer_size = this->_current_pos;
}

void		NetworkBuffer::gotoEnd()
{
  this->_current_pos = this->_buffer_size;
}

template <>
void		NetworkBuffer::serialize<std::string>(const std::string &element)
{
  this->serialize<unsigned int>(element.length());
  if (this->_buffer_size + element.length() > this->_buffer_max_size)
    {
      throw BufferException(this, std::string("Serialize std::string: no more space"));
    }
  for (auto it = element.begin(); it != element.end(); ++it)
    {
      this->_buffer[this->_current_pos] = *it;
      this->setPosition(this->getPosition() + 1);
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
      throw BufferException(this, std::string("Unserialize std::string: no more space"));
    }
  for (unsigned int i = 0; i < size; ++i)
    {
      element += this->_buffer[this->_current_pos];
      ++this->_current_pos;
    }
}

unsigned int	NetworkBuffer::getRemainingLength() const
{
  return (this->getLength() - this->getPosition());
}

unsigned int	NetworkBuffer::getOffset() const
{
  return (this->_offset);
}

void		NetworkBuffer::addOffset(int offset)
{
  if (static_cast<int>(this->_offset) + offset < 0)
    throw BufferException(this, "addOffset: Negative offset");
  if (static_cast<int>(this->_buffer_size) - offset < 0)
    throw BufferException(this, "addOffset: Not enough space");
  if (offset >= static_cast<int>(this->_current_pos))
    this->_current_pos = 0;
  else
    this->_current_pos -= offset;
  this->_buffer += offset;
  this->_buffer_size -= offset;
  this->_offset += offset;
}
