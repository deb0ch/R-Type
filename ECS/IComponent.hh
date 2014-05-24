#ifndef ICOMPONENT_H_
# define ICOMPONENT_H_

# include <string>

class		IComponent
{
public:
  virtual	~IComponent() {};

  virtual const std::string	&getType() const = 0;
  virtual IComponent *clone() const = 0;
};

#endif /* !ICOMPONENT_H_ */
