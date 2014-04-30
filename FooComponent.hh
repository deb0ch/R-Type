#ifndef FOOCOMPONENT_H_
# define FOOCOMPONENT_H_

#include	"IComponent.hh"

class		FooComponent : public IComponent
{
protected:
  int		_foo;

public:
  FooComponent(int foo);
  FooComponent(const FooComponent&);
  ~FooComponent();
  FooComponent&	operator=(const FooComponent&);
};

#endif /* !FOOCOMPONENT_H_ */
