#ifndef ENTITYSPAWNERSYSTEM_H_
# define ENTITYSPAWNERSYSTEM_H_

# include		"ASystem.hh"

class			EntitySpawnerSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *);
  virtual void		processEntity(Entity *, const float);

public:
  EntitySpawnerSystem();
  virtual		~EntitySpawnerSystem();
};

#endif /* !ENTITYSPAWNERSYSTEM_H_ */
