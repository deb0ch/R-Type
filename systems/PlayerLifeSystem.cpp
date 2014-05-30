#include "PlayerLifeSystem.hh"
#include "EntityDeletedEvent.hh"
#include "TagComponent.hh"
#include "IPlayerRespawner.hh"

PlayerLifeSystem::PlayerLifeSystem(unsigned int nb_lives) : ASystem("PlayerLifeSystem")
{
  this->_nb_lives = nb_lives;
}

PlayerLifeSystem::~PlayerLifeSystem()
{}

void	PlayerLifeSystem::init()
{
  this->_world->addEventHandler("EntityDeletedEvent", this, &PlayerLifeSystem::entityDeathEvent);
}

bool	PlayerLifeSystem::canProcess(Entity *)
{
  return (false);
}

void	PlayerLifeSystem::processEntity(Entity *, const float)
{}

void	PlayerLifeSystem::entityDeathEvent(IEvent *event)
{
  EntityDeletedEvent	*entityDeletedEvent = dynamic_cast<EntityDeletedEvent *>(event);
  IPlayerRespawner	*player_respawner;

  if (entityDeletedEvent)
    {
      TagComponent *tag = entityDeletedEvent->getEntity()->getComponent<TagComponent>("TagComponent");
      if (tag && tag->hasTag("PLAYER"))
	{
	  std::cout << "A player is dead!" << std::endl;
	  if (this->_nb_lives > 0)
	    {
	      --this->_nb_lives;
	      std::cout << "Player respawned! " << this->_nb_lives << " lives remaining!" << std::endl;
	      player_respawner = this->_world->getSharedObject<IPlayerRespawner>("PlayerRespawner");
	      if (!player_respawner)
		{
		  std::cerr << "No player respawner" << std::endl;
		  return ;
		}
	      player_respawner->playerRespawn(entityDeletedEvent->getEntity());
	    }
	  else
	    {
	      std::cout << "No lives remaining" << std::endl;
	    }
	}
    }
}
