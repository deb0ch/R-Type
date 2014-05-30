#include "SpawnPlayerSystem.hh"
#include "NewPlayerEvent.hh"
#include "NetworkPlayerComponent.hh"
#include "EntityFactory.hpp"
#include "NetworkSendActionComponent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "IPlayerRespawner.hh"

SpawnPlayerSystem::SpawnPlayerSystem(const std::vector<std::string> &entity_player_name)
  : ASystem("SpawnPlayerSystem"), _entity_player_name(entity_player_name), _index(0)
{}

SpawnPlayerSystem::~SpawnPlayerSystem()
{}

void SpawnPlayerSystem::init()
{
  this->_world->addEventHandler("NewPlayerEvent", this, &SpawnPlayerSystem::newPlayerHandler);
  this->_world->setSharedObject<IPlayerRespawner>("PlayerRespawner", this);
}

void			SpawnPlayerSystem::newPlayerHandler(IEvent *event)
{
  NewPlayerEvent	*new_player = dynamic_cast<NewPlayerEvent *>(event);

  std::cout << "New player :D" << std::endl;
  this->_players_to_spawn.push(new_player->getRemoteId());
}

bool		SpawnPlayerSystem::canProcess(Entity *)
{
  return false;
}

void		SpawnPlayerSystem::processEntity(Entity *, const float)
{}

void		SpawnPlayerSystem::updateWorldToRemote(Remote *remote)
{
  const std::vector<Entity *>	&entities = this->_world->getEntities();
  NetworkSendUpdateSystem	*update_system;

  update_system = this->_world->getSystem<NetworkSendUpdateSystem>("NetworkSendUpdateSystem");
  if (!update_system)
    std::cerr << "No update system??" << std::endl;
  std::for_each(entities.begin(), entities.end(),
		[&remote, &update_system] (const Entity *entity)
		{
		  update_system->updateEntityToRemote(remote,
						      entity,
						      entity->getComponent<NetworkSendUpdateComponent>
						      ("NetworkSendUpdateComponent"));
		});
}

void				SpawnPlayerSystem::playerRespawn(Entity *entity)
{
  NetworkPlayerComponent	*network_player_component;

  network_player_component = entity->getComponent<NetworkPlayerComponent>("NetworkPlayerComponent");
  if (network_player_component)
    this->spawnPlayer(network_player_component->getRemoteId(),
		      "PLAYER_RED"); // FIND A WAY TO GET THE NAME OF THE ENTITY
}

void		SpawnPlayerSystem::spawnNextPlayer(unsigned int hash)
{
  if (this->_index >= this->_entity_player_name.size())
    {
      std::cout << "Cannot spawn more player" << std::endl;
      std::cout << "..ok I'll do it.." << std::endl;
      this->_index = 0;
    }
  this->spawnPlayer(hash, this->_entity_player_name[this->_index]);
  ++this->_index;
}

void		SpawnPlayerSystem::spawnPlayer(unsigned int hash,
					       const std::string &entity_name)
{
  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");

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

      std::cout << "Created entity" << std::endl;
    }
}

void		SpawnPlayerSystem::beforeProcess(const float)
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
