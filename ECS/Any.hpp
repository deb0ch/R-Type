#ifndef ANY_HPP_
# define ANY_HPP_

# include <iostream>

class Any
{
public:
  Any()
  {
    this->_value = NULL;
  }

  virtual ~Any()
  {}

  template <typename T>
  Any(T *value)
  {
    this->_value = value;
  }

  template <typename T>
  const T *getValue() const
  {
    const T	*tmp;

    if (this->_value)
      {
	if (!(tmp = reinterpret_cast<const T *>(this->_value)))
	  std::cerr << "Bad type" << std::endl; // Raise exception
	return (tmp);
      }
    return (NULL);
  }

  template <typename T>
  T *getValue()
  {
    T	*tmp;

    if (this->_value)
      {
	if (!(tmp = reinterpret_cast<T *>(this->_value)))
	    std::cerr << "Bad type" << std::endl; // Raise exception
	return (tmp);
      }
    return (NULL);
  }

  template <typename T>
  Any &operator=(T *value)
  {
    this->_value = value;
    return (*this);
  }

  Any(const Any &other)
  {
    this->_value = other._value;
  }

  Any &operator=(const Any &other)
  {
    this->_value = other._value;
    return (*this);
  }

protected:
  void	*_value;
};

#endif /* !ANY_HPP_ */
