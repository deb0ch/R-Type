#include "FooComponent.hh"

//----- ----- Constructors ----- ----- //
FooComponent::FooComponent(int foo)
{
  this->_foo = foo;
}

FooComponent::FooComponent(const FooComponent&)
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
