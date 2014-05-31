#ifndef SPAWNPLAYERSYSTEM_H_
# define SPAWNPLAYERSYSTEM_H_

# include "ASystem.hh"
# include "SafeFifo.hpp"
# include "Remote.hh"
# include "IPlayerRespawner.hh"

class SpawnPlayerSystem : public ASystem, public IPlayerRespawner
{
public:
  SpawnPlayerSystem(const std::vector<std::string> &entity_player_name);
  virtual		~SpawnPlayerSystem();
  virtual void		init();
  virtual bool		canProcess(Entity *);
  virtual void		beforeProcess(const float);
  virtual void		processEntity(Entity *, const float delta);
  void			newPlayerHandler(IEvent *event);
  void			updateWorldToRemote(Remote *remote);
  virtual void		playerRespawn(Entity *entity);
  void			spawnNextPlayer(unsigned int hash);
  Entity		*spawnPlayer(unsigned int hash,
				     const std::string &entity_name);
  virtual void		registerDeadPlayer(Entity *entity);
  virtual bool		respawnDeadPlayer();

protected:
  SafeFifo<unsigned int>	_players_to_spawn;
  std::vector<std::string>	_entity_player_name;
  std::vector< std::pair<unsigned int, std::string> >	_dead_players;
  unsigned int			_index;
};

#endif /* !SPAWNPLAYERSYSTEM_H_ */
