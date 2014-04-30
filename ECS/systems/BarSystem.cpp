#include	<algorithm>
#include	<iostream>

#include	"BarSystem.hh"

//----- ----- Constructors ----- ----- //
BarSystem::BarSystem() : ASystem(5)
{}

BarSystem::BarSystem(const BarSystem&) : BarSystem()
{}

//----- ----- Destructor ----- ----- //
BarSystem::~BarSystem()
{}

//----- ----- Operators ----- ----- //
BarSystem&	BarSystem::operator=(const BarSystem&)
{
  return (*this);
}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //

//----- ----- Methods ----- ----- //
void		BarSystem::processEntity(Entity *entity)
{
  std::cout << "BarSystem is processing entity " << entity->_id << " !" << std::endl;
}

bool		BarSystem::canProcess(Entity *)
{
  return (true);
}
