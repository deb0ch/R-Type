#include	<iostream>

#include	"LifeSystem.hh"
#include	"LifeComponent.hh"
#include	"CollisionEvent.hh"
#include	"CollisionPowerComponent.hh"
#include	"EntityDeletedEvent.hh"
#include	"EntityFactory.hpp"
#include	"TagComponent.hh"

//----- ----- Constructors ----- ----- //
LifeSystem::LifeSystem()
  : ASystem("LifeSystem")
{}

//----- ----- Destructor ----- ----- //
LifeSystem::~LifeSystem()
{}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
//----- ----- Methods ----- ----- //
bool		LifeSystem::canProcess(Entity *e)
{
  if (e->hasComponent("LifeComponent"))
    return (true);
  return (false);
}

void			LifeSystem::processEntity(Entity *e, const float delta)
{
  LifeComponent *lifecompo;

  if (!(lifecompo = e->getComponent<LifeComponent>("LifeComponent")))
    return;
  if (lifecompo->getLife() <= 0)
    {
      this->_world->sendEvent(new EntityDeletedEvent(e));
      return;
    }
  if (lifecompo->isInvulnerable())
    lifecompo->decreaseInvulnerability(delta);
}

void			LifeSystem::collision_event(IEvent *e)
{
  CollisionEvent*	event = dynamic_cast<CollisionEvent*>(e);
  Entity *firstEntity = event->getEntity1();
  Entity *secondEntity = event->getEntity2();

  if (firstEntity == NULL || secondEntity == NULL)
    return;
  LifeComponent *lifeFirstE = firstEntity->getComponent<LifeComponent>("LifeComponent");
  CollisionPowerComponent *colPower = secondEntity->getComponent<CollisionPowerComponent>("CollisionPowerComponent");
  if (lifeFirstE == NULL || colPower == NULL)
    return;
  lifeFirstE->decreaseLife(colPower->getCollisionPower());
  TagComponent *tag = secondEntity->getComponent<TagComponent>("TagComponent");
  if (tag == NULL || !tag->hasTag("LASER"))
	  return;
  ExplosionComponent *explosionName = secondEntity->getComponent<ExplosionComponent>("ExplosionComponent");
  Pos2DComponent *position = secondEntity->getComponent<Pos2DComponent>("Pos2DComponent");
  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");
  if (explosionName != NULL && position != NULL && entityFactory != NULL)
  {
	  Entity *explode = entityFactory->create(explosionName->getExplosionEntityName());
	  Pos2DComponent *explodePosition = explode->getComponent<Pos2DComponent>("Pos2DComponent");
	  if (explode != NULL && explodePosition != NULL)
	  {
		  explodePosition->setX(position->getX() + explosionName->getOffsetX());
		  explodePosition->setY(position->getY() + explosionName->getOffsetY());
		  this->_world->addEntity(explode);
	  }
  }
}

void			LifeSystem::delete_entity(IEvent *e)
{
  EntityDeletedEvent*	event_catch = dynamic_cast<EntityDeletedEvent*>(e);
  if (event_catch == NULL)
    return;
  if (event_catch->isForced())
    return ;
  Entity *dyingEntity = event_catch->getEntity();
  if (dyingEntity == NULL)
    return;
  ExplosionComponent *explosionName = dyingEntity->getComponent<ExplosionComponent>("ExplosionComponent");
  Pos2DComponent *position = dyingEntity->getComponent<Pos2DComponent>("Pos2DComponent");
  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");
  if (explosionName != NULL && position != NULL && entityFactory != NULL)
  {
	  Entity *explode = entityFactory->create(explosionName->getExplosionEntityName());
	  if (explode == NULL)
		  return;
	  Pos2DComponent *explodePosition = explode->getComponent<Pos2DComponent>("Pos2DComponent");
	  if (explode != NULL && explodePosition != NULL)
	  {
		  explodePosition->setX(position->getX() + explosionName->getOffsetX());
		  explodePosition->setY(position->getY() + explosionName->getOffsetY());
		  this->_world->addEntity(explode);
	  }
  }
}
