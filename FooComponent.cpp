#include "FooComponent.hh"

//----- ----- Constructors ----- ----- //
FooComponent::FooComponent(int foo) : AComponent("FooComponent")
{
  this->_foo = foo;
}

FooComponent::FooComponent(const FooComponent&) : AComponent("FooComponent")
{}

//----- ----- Destructor ----- ----- //
FooComponent::~FooComponent()
{}

//----- ----- Operators ----- ----- //
FooComponent&	FooComponent::operator=(const FooComponent&)
{
  return (*this);
}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
