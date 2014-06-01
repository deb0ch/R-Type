#ifndef MOVESYSTEM_H_
# define MOVESYSTEM_H_

# include		"ASystem.hh"

class			MoveSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float);

public:
  MoveSystem();
  virtual		~MoveSystem();
};

#endif /* !MOVESYSTEM_H_ */
