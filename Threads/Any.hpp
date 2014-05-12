#ifndef ANY_HPP_
# define ANY_HPP_

# include <iostream>

class Any
{
private:
  class IContainer
  {
    public:
    virtual ~IContainer()
    {}

    virtual IContainer *clone() = 0;
  };

  template <typename T>
  class Container : public IContainer
  {
  public:
    Container(T *value)
    {
      this->_value = value;
    }

    virtual ~Container()
    {}

    virtual IContainer *clone()
    {
      return new Container<T>(this->_value);
    }

    T *_value;
  };
public:
  Any()
  {
    this->_container = NULL;
  }

  virtual ~Any()
  {
    if (this->_container)
      delete this->_container;
  }

  template <typename T>
  Any(T *value)
  {
    this->_container = new Container<T>(value);
  }

  template <typename T>
  const T *getValue() const
  {
    const Container<T>	*tmp;

    if (this->_container)
      {
	if (!(tmp = dynamic_cast<const Container<T> * >(this->_container)))
	  {
	    std::cerr << "Bad type" << std::endl; // Raise exception
	    return (NULL);
	  }
	return (tmp->_value);
      }
    return (NULL);
  }

  template <typename T>
  T *getValue()
  {
    Container<T>	*tmp;

    if (this->_container)
      {
	if (!(tmp = dynamic_cast< Container<T> * >(this->_container)))
	  {
	    std::cerr << "Bad type" << std::endl; // Raise exception
	    return (NULL);
	  }
	return (tmp->_value);
      }
    return (NULL);
  }

  template <typename T>
  Any &operator=(T *value)
  {
    if (this->_container)
      delete this->_container;
    this->_container = new Container<T>(value);
    return (*this);
  }

  Any(const Any &other)
  {
    this->_container = other._container->clone();
  }

  Any &operator=(const Any &other)
  {
    if (this->_container)
      delete this->_container;
    this->_container = other._container->clone();
    return (*this);
  }

protected:
  IContainer *_container;
};

#endif /* !ANY_HPP_ */
