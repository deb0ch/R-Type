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

//----- ----- Methods ----- ----- //
bool		MoveSystem::canProcess(Entity *e) const
{
  if (e->hasComponent("Speed2DComponent") && e->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void			MoveSystem::processEntity(Entity *e, const float deltaT)
{
  Speed2DComponent	*speed;
  Pos2DComponent	*pos;

  if (!(speed = e->getComponent<Speed2DComponent>("Speed2DComponent"))
      || !(pos = e->getComponent<Pos2DComponent>("Pos2DComponent")))
    return ;
  pos->setY(pos->getY() + speed->getVY() * deltaT);
  pos->setX(pos->getX() + speed->getVX() * deltaT);
}
