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

bool	PlayerLifeSystem::canProcess(Entity *) const
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
	  player_respawner = this->_world->getSharedObject<IPlayerRespawner>("PlayerRespawner");
	  if (!player_respawner)
	    {
	      std::cerr << "No player respawner" << std::endl;
	      return ;
	    }
	  if (this->_nb_lives > 0)
	    {
	      --this->_nb_lives;
	      player_respawner->playerRespawn(entityDeletedEvent->getEntity());
	    }
	  else
	    player_respawner->registerDeadPlayer(entityDeletedEvent->getEntity());
	}
    }
}

unsigned int	PlayerLifeSystem::getNbLives() const
{
  return this->_nb_lives;
}

void			PlayerLifeSystem::setNbLives(unsigned int lives)
{
  IPlayerRespawner	*player_respawner;

  this->_nb_lives = lives;
  if (this->_nb_lives)
    {
      player_respawner = this->_world->getSharedObject<IPlayerRespawner>("PlayerRespawner");
      if (!player_respawner)
	{
	  std::cerr << "No player respawner" << std::endl;
	  return ;
	}
      while (player_respawner->respawnDeadPlayer())
	;
    }
}
