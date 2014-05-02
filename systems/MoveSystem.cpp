#include	<iostream>

#include	"MoveSystem.hh"

//----- ----- Constructors ----- ----- //
MoveSystem::MoveSystem()
  : ASystem("MoveSystem")
{}

//----- ----- Destructor ----- ----- //
MoveSystem::~MoveSystem()
{}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
//----- ----- Methods ----- ----- //
bool		MoveSystem::canProcess(Entity *)
{
  return (true);
}

void		MoveSystem::processEntity(Entity *, const float)
{
  std::cout << "yeah" << std::endl;
}

void		MoveSystem::sortEntities(std::vector<Entity *>&)
{

}
