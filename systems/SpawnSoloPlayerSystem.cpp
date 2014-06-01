#include "SpawnSoloPlayerSystem.hh"
#include "NewPlayerEvent.hh"
#include "NetworkPlayerComponent.hh"
#include "EntityFactory.hpp"
#include "NetworkSendActionComponent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "IPlayerRespawner.hh"

SpawnSoloPlayerSystem::SpawnSoloPlayerSystem(const std::string &entity_player_name)
: ASystem("SpawnPlayerSystem"), _entity_player_name(entity_player_name)
{}

SpawnSoloPlayerSystem::~SpawnSoloPlayerSystem()
{}

void SpawnSoloPlayerSystem::init()
{
  this->_world->addEventHandler("NewPlayerEvent", this, &SpawnSoloPlayerSystem::newPlayerHandler);
  this->_world->setSharedObject<IPlayerRespawner>("PlayerRespawner", this);
}

void			SpawnSoloPlayerSystem::newPlayerHandler(IEvent *event)
{
  NewPlayerEvent	*new_player = dynamic_cast<NewPlayerEvent *>(event);

  this->_players_to_spawn.push(new_player->getRemoteId());
}

bool		SpawnSoloPlayerSystem::canProcess(Entity *)
{
  return false;
}

void		SpawnSoloPlayerSystem::processEntity(Entity *, const float)
{}

void				SpawnSoloPlayerSystem::playerRespawn(Entity *)
{
  this->spawnPlayer(this->_entity_player_name);
}

void		SpawnSoloPlayerSystem::spawnNextPlayer()
{
  this->spawnPlayer(this->_entity_player_name);
}

Entity		*SpawnSoloPlayerSystem::spawnPlayer(const std::string &entity_name)
{
  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");
  LifeComponent *life_component;

  if (entityFactory)
    {
      Entity *player_entity = entityFactory->create(entity_name);
      this->_world->addEntity(player_entity);
      if (player_entity)
	{
	  Entity *player_entity = entityFactory->create(entity_name);
	  this->_world->addEntity(player_entity);
	  if (player_entity)
	    {
	      life_component = player_entity->getComponent<LifeComponent>("LifeComponent");
	      if (life_component)
		life_component->setInvulnerabilityTime(3.f);
	    }
	  return (player_entity);
	}
      return (player_entity);
    }
  return (NULL);
}

void		SpawnSoloPlayerSystem::beforeProcess(const float)
{
  while (!this->_players_to_spawn.isEmpty())
    {
      this->spawnNextPlayer();
    }
}

void		SpawnSoloPlayerSystem::registerDeadPlayer(Entity *)
{
  this->_dead_players.push_back(this->_entity_player_name);
}

bool		SpawnSoloPlayerSystem::respawnDeadPlayer()
{
  if (this->_dead_players.empty())
    return false;
  this->spawnPlayer(this->_dead_players.front());
  this->_dead_players.erase(this->_dead_players.begin());
  return true;
}
