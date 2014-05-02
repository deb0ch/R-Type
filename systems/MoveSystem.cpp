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
bool		MoveSystem::canProcess(Entity *e)
{
  if (e->hasComponent("Speed2DComponent") && e->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void		MoveSystem::processEntity(Entity *)
{
  if (e->hasComponent("Speed2DComponent"))
  std::cout << "yeah" << std::endl;
}
