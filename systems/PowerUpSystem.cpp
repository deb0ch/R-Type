#include	"PowerUpSystem.hh"
#include	"CollisionEvent.hh"
#include	"PowerUpComponent.hh"
#include	"EntitySpawnerComponent.hh"

PowerUpSystem::PowerUpSystem()
	: ASystem("PowerUpSystem")
{}

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