#include "SpawnPlayerSystem.hh"
#include "NewPlayerEvent.hh"
#include "NetworkPlayerComponent.hh"
#include "EntityFactory.hpp"
#include "NetworkSendActionComponent.hh"

SpawnPlayerSystem::SpawnPlayerSystem() : ASystem("SpawnPlayerSystem")
{}

SpawnPlayerSystem::~SpawnPlayerSystem()
{}

void SpawnPlayerSystem::init()
{
  this->_world->addEventHandler("NewPlayerEvent", this, &SpawnPlayerSystem::newPlayerHandler);
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
	{
	  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");

	  if (entityFactory)
	    {
	      Entity *player_entity = entityFactory->create("PLAYER_RED");
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
	      				  ->addPlayerComponent(player_entity->getComponent<ASerializableComponent>("ActionComponent"))
	      				  ->addPlayerComponent(player_entity->getComponent<ASerializableComponent>("Friction2DComponent"))
	      				  ->addPlayerComponent(send_action));

	      std::cout << "Created entity" << std::endl;
	    }
	}
    }
}
