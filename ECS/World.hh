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
  ~World();
  World&	operator=(const World&);

  Entity	*createEntity();

  Entity	*addEntity(Entity *);
  World		*addSystem(ISystem *);

  void		process();
};

#endif /* !WORLD_H_ */
