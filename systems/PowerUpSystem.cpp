#include	"PowerUpSystem.hh"
#include	"CollisionEvent.hh"
#include	"PowerUpComponent.hh"
#include	"EntitySpawnerComponent.hh"
#include	"EntityDeletedEvent.hh"
#include	"TagComponent.hh"
#include	"RandomInt.hpp"
#include	"EntityFactory.hpp"

PowerUpSystem::PowerUpSystem()
	: ASystem("PowerUpSystem")
{
}

PowerUpSystem::~PowerUpSystem()
{}

bool PowerUpSystem::canProcess(Entity *)
{
	return (false);
}

void PowerUpSystem::processEntity(Entity *, const float)
{}

void PowerUpSystem::collision_event(IEvent *e)
{
	CollisionEvent*	event = dynamic_cast<CollisionEvent*>(e);
	Entity *firstEntity = event->getEntity1();
	Entity *secondEntity = event->getEntity2();

	PowerUpComponent *powerUp = firstEntity->getComponent<PowerUpComponent>("PowerUpComponent");
	if (powerUp == NULL)
		return ;
	EntitySpawnerComponent *spawner = secondEntity->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent");
	if (spawner == NULL)
		return;
	powerUp->upgrade(spawner);
}
void PowerUpSystem::delete_entity(IEvent *e)
{
	EntityDeletedEvent*	event_catch = dynamic_cast<EntityDeletedEvent*>(e);
	if (event_catch == NULL)
		return;
	Entity *dyingEntity = event_catch->getEntity();
	if (dyingEntity == NULL)
		return;
	Pos2DComponent *position = dyingEntity->getComponent<Pos2DComponent>("Pos2DComponent");
	EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");
	TagComponent *tag = dyingEntity->getComponent<TagComponent>("TagComponent");
	if (tag == NULL || position == NULL || entityFactory == NULL)
		return;
	if (tag->hasTag("MONSTER"))
	{
		if (RandomInt().operator()<unsigned long>(0, 10) == 0)
		{
			std::vector<std::string> powerup;
			powerup.push_back("POWERUP_1");
			powerup.push_back("POWERUP_2");
			powerup.push_back("POWERUP_3");

			Entity *boost = entityFactory->create(powerup[RandomInt().operator()<unsigned long>(0, powerup.size() - 1)]);
			if (boost == NULL)
				return;
			Pos2DComponent *boostPosition = boost->getComponent<Pos2DComponent>("Pos2DComponent");
			if (boostPosition == NULL)
				return;
			boostPosition->setX(position->getX());
			boostPosition->setY(position->getY());
			this->_world->addEntity(boost);
		}
	}
}
