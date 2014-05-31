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
	this->spawnPlayer("PLAYER_RED"); // FIND A WAY TO GET THE NAME OF THE ENTITY
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
			[&hash](const Entity *entity)
		{
			return false;
		});
		if (!player_found)
			this->spawnNextPlayer();
	}
}

void		SpawnSoloPlayerSystem::registerDeadPlayer(Entity *entity)
{
		this->_dead_players.push_back("PLAYER_RED"); // FIND A WAY TO GET THE NAME OF THE ENTITY
}

bool		SpawnSoloPlayerSystem::respawnDeadPlayer()
{
	if (this->_dead_players.empty())
		return false;
	this->spawnPlayer(this->_dead_players.front());
	this->_dead_players.erase(this->_dead_players.begin());
	return true;
}
