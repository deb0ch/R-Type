#ifndef NETWORKBUFFER_H_
# define NETWORKBUFFER_H_

# include <iostream>
# include "IBuffer.hh"

class NetworkBuffer : public IBuffer
{
public:
  NetworkBuffer(unsigned int size = 512);
  virtual ~NetworkBuffer();
  NetworkBuffer(const IBuffer &);
  virtual IBuffer &operator=(const IBuffer &);

  static bool		isBigEndian()
  {
    static const short	dummy_value = 0x00FF;
    static const char	*dummy_tab = reinterpret_cast<const char *>(&dummy_value);

    return (dummy_tab[0] == 0x00);
  }

  virtual IBuffer	&operator<<(const int &);
  virtual IBuffer	&operator<<(const unsigned int &);
  virtual IBuffer	&operator<<(const unsigned long &);
  virtual IBuffer	&operator<<(const float &);
  virtual IBuffer	&operator<<(const std::string &);
  virtual IBuffer	&operator<<(const char &);

  virtual IBuffer	&operator>>(int &);
  virtual IBuffer	&operator>>(unsigned int &);
  virtual IBuffer	&operator>>(unsigned long &);
  virtual IBuffer	&operator>>(float &);
  virtual IBuffer	&operator>>(std::string &);
  virtual IBuffer	&operator>>(char &);

  virtual bool		end() const;
  virtual void		rewind();
  virtual void		reset();
  virtual const char	*getBuffer() const;
  virtual char		*getBuffer();
  virtual unsigned int	getLength() const;
  virtual void		setLength(unsigned int);
  virtual unsigned int	getMaxSize() const;

  virtual unsigned int	getPosition() const;
  virtual void		setPosition(unsigned int);

protected:
  const unsigned int	bufferMaxSize;
  char			*_buffer;
  unsigned int		_buffer_size;
  unsigned int		_current_pos;

private:
  template <typename T>
  void		serialize(const T &elements)
  {
    size_t i;
    const char	*tab;

    tab = reinterpret_cast<const char *>(&elements);
    if (this->_buffer_size + sizeof(T) > bufferMaxSize)
      {
	std::cout << "Not enough space" << std::endl; // raise exception
	return ;
      }
    if (isBigEndian())
      i = 0;
    else
      i = sizeof(T) - 1;
    while ((isBigEndian() && i < sizeof(T)) || (!isBigEndian() && i >= 0))
      {
	this->_buffer[this->_buffer_size] = tab[i];
	if (isBigEndian())
	  ++i;
	else
	  --i;
	++this->_buffer_size;
      }
  };

  template <typename T>
  void		unserialize(T &elements)
  {
    size_t	i;
    char	*tab;

    tab = reinterpret_cast<char *>(&elements);
    if (this->_buffer_size - this->_current_pos < sizeof(T))
      {
	std::cout << "Not enough space" << std::endl; // raise exception
	return ;
      }
    if (isBigEndian())
      i = 0;
    else
      i = sizeof(T) - 1;
    while ((isBigEndian() && i < sizeof(T)) || (!isBigEndian() && i >= 0))
      {
	tab[i] = this->_buffer[this->_current_pos];
	if (isBigEndian())
	  ++i;
	else
	  --i;
	++this->_current_pos;
      }
  }
};

template <>
void		NetworkBuffer::serialize<std::string>(const std::string &element);
template <>
void		NetworkBuffer::unserialize<std::string>(std::string &element);

#endif /* !NETWORKBUFFER_H_ */
