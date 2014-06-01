#ifndef SPAWNSOLOPLAYERSYSTEM_H_
# define SPAWNSOLOPLAYERSYSTEM_H_

# include "ASystem.hh"
# include "SafeFifo.hpp"
# include "Remote.hh"
# include "IPlayerRespawner.hh"

class SpawnSoloPlayerSystem : public ASystem, public IPlayerRespawner
{
public:
  SpawnSoloPlayerSystem(const std::string &entity_player_name);
  virtual		~SpawnSoloPlayerSystem();
  virtual void		init();
  virtual bool		canProcess(Entity *) const;
  virtual void		beforeProcess(const float);
  virtual void		processEntity(Entity *, const float delta);

  void			newPlayerHandler(IEvent *event);
  virtual void		playerRespawn(Entity *entity);
  void			spawnNextPlayer();
  Entity		*spawnPlayer(const std::string &entity_name);
  virtual void		registerDeadPlayer(Entity *entity);
  virtual bool		respawnDeadPlayer();

protected:
  SafeFifo<unsigned int>	_players_to_spawn;
  std::string		_entity_player_name;
  std::vector<std::string>	_dead_players;
};

#endif /* !SPAWNSOLOPLAYERSYSTEM_H_ */
