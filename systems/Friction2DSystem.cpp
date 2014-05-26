#include	<iostream>

#include	"Friction2DSystem.hh"
#include	"Friction2DComponent.hh"
#include	"Speed2DComponent.hh"

//----- ----- Constructors ----- ----- //
Friction2DSystem::Friction2DSystem()
  : ASystem("Friction2DSystem")
{}

//----- ----- Destructor ----- ----- //
Friction2DSystem::~Friction2DSystem()
{}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
//----- ----- Methods ----- ----- //
bool		Friction2DSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("Speed2DComponent") && entity->hasComponent("Friction2DComponent"))
    return (true);
  return (false);
}

/**
 * Decreases the speed of the component. The formula is newSpeed = oldSpeed / (coef + 1)
 * Therefore, if coef = 0 the speed is not affected.
 * If 0 < coef, the speed is decreased
 * If -1 < coef < 0, the speed is increased
 */
void			Friction2DSystem::processEntity(Entity *entity, const float)
{
  Speed2DComponent	*speed;
  Friction2DComponent	*friction;

  speed = entity->getComponent<Speed2DComponent>("Speed2DComponent");
  friction = entity->getComponent<Friction2DComponent>("Friction2DComponent");
  if (friction->getFrictionCoef() <= -1)
    return ;
  speed->setVX(speed->getVX() / (friction->getFrictionCoef() + 1.f));
  speed->setVY(speed->getVY() / (friction->getFrictionCoef() + 1.f));
}
