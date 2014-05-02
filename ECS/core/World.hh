#ifndef WORLD_H_
# define WORLD_H_

# include	<vector>

# include	"Entity.hh"
# include	"ISystem.hh"

class		World
{
private:
  std::vector<Entity*>	_entities;
  std::vector<ISystem*>	_systems;
  unsigned long		_nextEntityID;

public:
		World();
		World(const World&);
  virtual	~World();
  World&	operator=(const World&);

  Entity	*createEntity();

  World		*addEntity(Entity *);
  World		*addSystem(ISystem *);
  World		*removeEntity(Entity *);
  World		*removeEntity(unsigned long id);
  World		*removeSystem(ISystem *);
  World		*removeSystem(const std::string &type);

  std::vector<Entity *> &getEntities();

  void		process();
};

#endif /* !WORLD_H_ */
