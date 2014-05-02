#ifndef ICOMPONENT_H_
# define ICOMPONENT_H_

# include <string>

class		IComponent
{
public:
		IComponent() {};
  virtual	~IComponent() {};

  virtual const std::string	&getType() const = 0;
};

#endif /* !ICOMPONENT_H_ */
