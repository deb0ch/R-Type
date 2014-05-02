#ifndef ACOMPONENT_H_
# define ACOMPONENT_H_

# include	<string>
# include	"IComponent.hh"

class		AComponent : public IComponent
{
protected:
  std::string	_type;

public:
  AComponent() = delete;
  AComponent(const std::string &type);
  virtual	~AComponent();

  virtual const std::string	&getType() const;
};

#endif /* !ACOMPONENT_H_ */
