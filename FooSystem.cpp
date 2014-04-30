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
void		FooSystem::process(std::vector<Entity *> &entities)
{
  std::for_each(entities.begin(), entities.end(), [](Entity *entity) -> void {
      std::cout << "FooSystem is processing entity " << entity->_id << " !" << std::endl;
	});
}
