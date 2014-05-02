#ifndef MOVESYSTEM_H_
# define MOVESYSTEM_H_

# include		"ASystem.hh"

class			MoveSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *);
  virtual void		sortEntities(std::vector<Entity *>&);

public:
  MoveSystem();
  virtual		~MoveSystem();
};

#endif /* !MOVESYSTEM_H_ */
