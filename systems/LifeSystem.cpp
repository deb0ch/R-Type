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
		/*Pos2DComponent *position = e->getComponen<Pos2DComponent>("Pos2DComponent");
		if (position != NULL)
		{
			EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");
			if (entityFactory == NULL)
				return;
			Entity *explosion = entityFactory->create("EXPLODE");
			explosion->getComponent<Pos2DComponent>("Pos2DComponent")->setX(position->getX());
			explosion->getComponent<Pos2DComponent>("Pos2DComponent")->setY(position->getY());
			this->_world->addEntity(explosion);
		}*/
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