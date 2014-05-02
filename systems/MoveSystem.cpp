#include	<iostream>

#include	"MoveSystem.hh"
#include	"Speed2DComponent.hh"
#include	"Pos2DComponent.hh"

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

void			MoveSystem::processEntity(Entity *e, const float)
{
  Speed2DComponent	*speed;
  Pos2DComponent	*pos;

  if (!(speed = e->getComponent<Speed2DComponent>("Speed2DComponent")) ||
      !(pos = e->getComponent<Pos2DComponent>("Pos2DComponent")))
    return ;
  pos->setY(pos->getY() + speed->getVY());
  pos->setX(pos->getX() + speed->getVX());
  /*  tests */
  std::cout << "y = " << pos->getY() << " et x = " << pos->getX() << std::endl;
}
