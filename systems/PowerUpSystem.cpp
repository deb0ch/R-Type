#include	"PowerUpSystem.hh"
#include	"CollisionEvent.hh"
#include	"APowerUpComponent.hpp"
#include	"EntitySpawnerComponent.hh"
#include	"EntityDeletedEvent.hh"
#include	"TagComponent.hh"
#include	"RandomInt.hpp"
#include	"EntityFactory.hpp"

PowerUpSystem::PowerUpSystem(const std::vector<std::string> &possible_powerup,
			     const std::vector<std::string> &powerup_component_names)
  : ASystem("PowerUpSystem")
{
  this->_possible_powerup = possible_powerup;
  this->_powerup_component_names = powerup_component_names;
}

PowerUpSystem::~PowerUpSystem()
{}

void	PowerUpSystem::init()
{
  this->_world->addEventHandler("CollisionEvent", this, &PowerUpSystem::collision_event);
  this->_world->addEventHandler("EntityDeletedEvent", this, &PowerUpSystem::delete_entity);
}

bool PowerUpSystem::canProcess(Entity *) const
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
	APowerUpComponent *powerUp = NULL;

	for (auto it = this->_powerup_component_names.begin();
	     it != this->_powerup_component_names.end() && powerUp == NULL;
	     ++it)
	  {
	    powerUp = firstEntity->getComponent<APowerUpComponent>(*it);
	  }
	if (powerUp == NULL)
	  return ;
	powerUp->upgrade(this->_world, secondEntity);
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
			Entity *boost =
			  entityFactory->create(this->_possible_powerup[
								       RandomInt().operator()<unsigned long>
								       (0, this->_possible_powerup.size() - 1)
								       ]);
			if (boost == NULL)
			  {
			    std::cout << "Boost is null" << std::endl;
			    return;
			  }
			Pos2DComponent *boostPosition = boost->getComponent<Pos2DComponent>("Pos2DComponent");
			if (boostPosition == NULL)
				return;
			boostPosition->setX(position->getX());
			boostPosition->setY(position->getY());
			this->_world->addEntity(boost);
		}
	}
}
