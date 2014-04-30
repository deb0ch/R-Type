#ifndef FOOCOMPONENT_H_
# define FOOCOMPONENT_H_

#include "AComponent.hh"

class		FooComponent : public AComponent
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
