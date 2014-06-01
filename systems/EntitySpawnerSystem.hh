#ifndef ENTITYSPAWNERSYSTEM_H_
# define ENTITYSPAWNERSYSTEM_H_

# include		"ASystem.hh"

# include		"EntitySpawnerComponent.hh"

class			EntitySpawnerSystem : public ASystem
{
protected:
  virtual bool		canProcess(Entity *) const;
  virtual void		processEntity(Entity *, const float);

private:
  void			givePosition(Entity *e, EntitySpawnerComponent *spawner, Entity *res) const;
  void			giveTeam(Entity *e, Entity *res) const;
  void			giveComponents(EntitySpawnerComponent *spawner, Entity *res) const;

public:
  EntitySpawnerSystem();
  virtual		~EntitySpawnerSystem();
};

#endif /* !ENTITYSPAWNERSYSTEM_H_ */
