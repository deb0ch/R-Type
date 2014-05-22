#include	<iostream>

#include	"LifeSystem.hh"
#include	"LifeComponent.hh"
#include	"CollisionEvent.hh"
#include	"CollisionPowerComponent.hh"
#include	"EntityDeletedEvent.hh"
#include	"EntityFactory.hpp"

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

void			LifeSystem::processEntity(Entity *e, const float)
{
	LifeComponent *lifecompo;

	if (!(lifecompo = e->getComponent<LifeComponent>("LifeComponent")))
		return;
	if (lifecompo->getLife() <= 0)
	{
		this->_world->sendEvent(new EntityDeletedEvent(e));
		ExplosionComponent *explosionName = e->getComponent<ExplosionComponent>("ExplosionComponent");
		if (explosionName == NULL)
			return;
		Pos2DComponent *position = e->getComponent<Pos2DComponent>("Pos2DComponent");
		if (position == NULL)
			return;
		EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");
		if (entityFactory == NULL)
			return;
		Entity *explode = entityFactory->create(explosionName->getExplosionEntityName());
		if (explode == NULL)
			return;
		Pos2DComponent *explodePosition = explode->getComponent<Pos2DComponent>("Pos2DComponent");
		if (explodePosition == NULL)
			return;
		explodePosition->setX(position->getX());
		explodePosition->setY(position->getY());
		this->_world->addEntity(explode);
		return;
	}
	if (lifecompo->isInvulnerable())
		lifecompo->decreaseInvulnerability();
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
	std::cout << "Collision between " << firstEntity->getId()
		<< " and " << secondEntity->getId() << std::endl;
}