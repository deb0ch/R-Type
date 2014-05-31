#ifndef IPLAYERRESPAWNER_H_
# define IPLAYERRESPAWNER_H_

# include "Entity.hh"

class IPlayerRespawner
{
public:
  virtual	~IPlayerRespawner()
  {}
  virtual void		playerRespawn(Entity *entity) = 0;
  virtual void		registerDeadPlayer(Entity *entity) = 0;
  virtual bool		respawnDeadPlayer() = 0;

protected:

};

#endif /* !IPLAYERRESPAWNER_H_ */
