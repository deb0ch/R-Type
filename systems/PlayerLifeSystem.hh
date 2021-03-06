#ifndef PLAYERLIFESYSTEM_H_
# define PLAYERLIFESYSTEM_H_

# include "ASystem.hh"

class PlayerLifeSystem : public ASystem
{
public:
  PlayerLifeSystem(unsigned int nb_lives = 3);
  virtual ~PlayerLifeSystem();
  virtual void	init();
  virtual bool	canProcess(Entity *) const;
  virtual void	processEntity(Entity *, const float);
  void		savePlayerDeath(Entity *);
  void		entityDeathEvent(IEvent *event);
  unsigned int	getNbLives() const;
  void		setNbLives(unsigned int);
protected:
  unsigned int _nb_lives;
};

#endif /* !PLAYERLIFESYSTEM_H_ */
