#ifndef SCORESYSTEM_H_
# define SCORESYSTEM_H_

# include "ASystem.hh"

class ScoreSystem : public ASystem
{
public:
  ScoreSystem();
  virtual ~ScoreSystem();
  virtual void	init();
  virtual bool	canProcess(Entity *);
  virtual void	processEntity(Entity *, const float);
  void		entityDeathEvent(IEvent *event);
  unsigned int	getScore() const;

protected:
  unsigned int _score;

};

#endif /* !SCORESYSTEM_H_ */
