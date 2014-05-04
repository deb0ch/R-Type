#ifndef ACOMPONENT_H_
# define ACOMPONENT_H_

# include	<string>
# include	"IComponent.hh"

template <typename T>
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

  virtual IComponent *clone() const
  {
    return (new T(*dynamic_cast<const T *>(this)));
  }

  virtual const std::string	&getType() const
  {
    return (this->_type);
  }
};

#endif /* !ACOMPONENT_H_ */
