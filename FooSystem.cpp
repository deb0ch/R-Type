#include	<algorithm>
#include	<iostream>

#include	"FooSystem.hh"

//----- ----- Constructors ----- ----- //
FooSystem::FooSystem()
{}

FooSystem::FooSystem(const FooSystem&)
{}

//----- ----- Destructor ----- ----- //
FooSystem::~FooSystem()
{}

//----- ----- Operators ----- ----- //
FooSystem&	FooSystem::operator=(const FooSystem&)
{
  return (*this);
}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //

//----- ----- Methods ----- ----- //
void		FooSystem::processEntity(Entity *entity)
{
  std::cout << "FooSystem is processing entity " << entity->_id << " !" << std::endl;
}

bool		FooSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("FooComponent"))
    return (true);
  return (false);
}
