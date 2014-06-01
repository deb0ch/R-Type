# include "Friction2DSystem.hh"

//----- ----- Constructors ----- ----- //
Friction2DSystem::Friction2DSystem()
  : ASystem("Friction2DSystem")
{}

//----- ----- Destructor ----- ----- //
Friction2DSystem::~Friction2DSystem()
{}

//----- ----- Methods ----- ----- //
bool		Friction2DSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("Speed2DComponent") && entity->hasComponent("Friction2DComponent"))
    return (true);
  return (false);
}

/**
 * Decreases the speed of the component. The formula is newSpeed = oldSpeed - coef * delta
 */
void			Friction2DSystem::processEntity(Entity *entity, const float delta)
{
  Speed2DComponent*	speed;
  Friction2DComponent*	friction;

  speed = entity->getComponent<Speed2DComponent>("Speed2DComponent");
  friction = entity->getComponent<Friction2DComponent>("Friction2DComponent");

  speed->setVX(applyFriction(speed->getVX(), friction->getFrictionCoef(), delta));
  speed->setVY(applyFriction(speed->getVY(), friction->getFrictionCoef(), delta));
}

float	Friction2DSystem::applyFriction(float oldSpeed, float friction, float delta)
{
  return (oldSpeed * expf(-friction * delta));
}
