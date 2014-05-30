#ifndef IPLAYERRESPAWNER_H_
# define IPLAYERRESPAWNER_H_

# include "Entity.hh"

class IPlayerRespawner
{
public:
  virtual	~IPlayerRespawner()
  {}
  virtual void	playerRespawn(Entity *entity) = 0;

protected:

};

#endif /* !IPLAYERRESPAWNER_H_ */
