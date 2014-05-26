#ifndef SPAWNPLAYERSYSTEM_H_
# define SPAWNPLAYERSYSTEM_H_

# include "ASystem.hh"
# include "SafeFifo.hpp"

class SpawnPlayerSystem : public ASystem
{
public:
  SpawnPlayerSystem();
  virtual		~SpawnPlayerSystem();
  virtual void		init();
  virtual bool		canProcess(Entity *);
  virtual void		beforeProcess();
  virtual void		processEntity(Entity *, const float delta);
  void			newPlayerHandler(IEvent *event);
protected:
  SafeFifo<unsigned int>	_players_to_spawn;
};

#endif /* !SPAWNPLAYERSYSTEM_H_ */
