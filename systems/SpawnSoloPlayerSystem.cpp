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

  std::cout << "New player :D" << std::endl;
  this->_players_to_spawn.push(new_player->getRemoteId());
}

bool		SpawnSoloPlayerSystem::canProcess(Entity *)
{
  return false;
}

void		SpawnSoloPlayerSystem::processEntity(Entity *, const float)
{}

void				SpawnSoloPlayerSystem::playerRespawn(Entity *entity)
{
	//this->spawnPlayer(network_player_component->getRemoteId(), "PLAYER_RED"); // FIND A WAY TO GET THE NAME OF THE ENTITY
}

void		SpawnSoloPlayerSystem::spawnNextPlayer(unsigned int hash)
{
  this->spawnPlayer(hash, this->_entity_player_name);
}

Entity		*SpawnSoloPlayerSystem::spawnPlayer(unsigned int hash,
					       const std::string &entity_name)
{
  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");
  LifeComponent *life_component;

  if (entityFactory)
    {
      Entity *player_entity = entityFactory->create(entity_name);
      this->_world->addEntity(player_entity);
      NetworkSendActionComponent *send_action = new NetworkSendActionComponent(player_entity->_id);
      ASerializableComponent *tmp;
      // tmp = player_entity->getComponent<ASerializableComponent>("Pos2DComponent");
      // if (tmp)
      // 	tmp->setNetworkSendUpdateException(hash);
      tmp = player_entity->getComponent<ASerializableComponent>("Speed2DComponent");
      if (tmp)
	tmp->setNetworkSendUpdateException(hash);
      player_entity->addComponent((new NetworkPlayerComponent(hash))
				  ->addPlayerComponent(player_entity->getComponent<ASerializableComponent>
						       ("ActionComponent"))
				  ->addPlayerComponent(player_entity->getComponent<ASerializableComponent>
						       ("Friction2DComponent"))
				  ->addPlayerComponent(send_action));
      if (player_entity)
	{
	  life_component = player_entity->getComponent<LifeComponent>("LifeComponent");
	  if (life_component)
	    life_component->setInvulnerabilityTime(3.f);
	  std::cout << "Created entity" << std::endl;
	}
      return (player_entity);
    }
  return (NULL);
}

void		SpawnSoloPlayerSystem::beforeProcess(const float)
{
  unsigned int	hash;
  bool		player_found;

  while (!this->_players_to_spawn.isEmpty())
    {
      hash = this->_players_to_spawn.getNextPop();
      const std::vector<Entity *> &entities = this->_world->getEntities();
      player_found = std::any_of(entities.begin(), entities.end(),
				 [&hash] (const Entity *entity)
				 {
				   NetworkPlayerComponent *component;

				   component =
				   entity->getComponent<NetworkPlayerComponent>("NetworkPlayerComponent");
				   if (component)
				     {
				       if (component->getRemoteId() == hash)
					 return true;
				     }
				   return false;
				 });
      if (!player_found)
	this->spawnNextPlayer(hash);
    }
}

void		SpawnSoloPlayerSystem::registerDeadPlayer(Entity *entity)
{
  NetworkPlayerComponent	*network_player_component;

  network_player_component = entity->getComponent<NetworkPlayerComponent>("NetworkPlayerComponent");
  if (network_player_component && network_player_component->canRespawn())
    {
      this->_dead_players.push_back(std::make_pair(network_player_component->getRemoteId(),
						   "PLAYER_RED")); // FIND A WAY TO GET THE NAME OF THE ENTITY
    }
}

bool		SpawnSoloPlayerSystem::respawnDeadPlayer()
{
  if (this->_dead_players.empty())
    return false;
  this->spawnPlayer(this->_dead_players.front().first, this->_dead_players.front().second);
  this->_dead_players.erase(this->_dead_players.begin());
  return true;
}
