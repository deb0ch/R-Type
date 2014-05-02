#include	<algorithm>

#include	"VectorDeleter.hpp"
#include	"World.hh"

//----- ----- Constructors ----- ----- //
World::World()
{
  this->_nextEntityID = 1;
}

World::World(const World& ref)
{
  this->_entities = ref._entities;
  this->_systems = ref._systems;
}

//----- ----- Destructor ----- ----- //
World::~World()
{
  std::for_each(this->_entities.begin(), this->_entities.end(), VectorDeleter<Entity*>());
  std::for_each(this->_systems.begin(), this->_systems.end(), VectorDeleter<ISystem*>());
}

//----- ----- Operators ----- ----- //
World&	World::operator=(const World& ref)
{
  this->_entities = ref._entities;
  this->_systems = ref._systems;
  return (*this);
}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
Entity	*World::createEntity()
{
  Entity	*res;

  res = new Entity();
  res->_id = this->_nextEntityID++;
  return (res);
}

World	*World::addEntity(Entity *entity)
{
  this->_entities.push_back(entity);
  if (entity->_id >= this->_nextEntityID)
    _nextEntityID = entity->_id + 1;
  return (this);
}

World	*World::addSystem(ISystem *system)
{
  this->_systems.push_back(system);
  system->setWorld(this);
  std::sort(this->_systems.begin(), this->_systems.end(), [] (const ISystem *system_a,
							      const ISystem *system_b) -> bool {
	      return (system_a->getPriority() > system_b->getPriority());
	    });
  return (this);
}

World	*World::removeEntity(Entity *entity)
{
  if (entity)
    return (this->removeEntity(entity->_id));
  return (NULL);
}

World	*World::removeEntity(unsigned long id)
{
  auto it = std::find_if(this->_entities.begin(), this->_entities.end(),
			 [id] (Entity *entity) -> bool {
			   return (entity->_id == id);
			 });

  if (it == this->_entities.end())
    return (NULL);

  delete *it;
  this->_entities.erase(it);
  return (this);
}

World	*World::removeSystem(ISystem *system)
{
  if (system)
    return (this->removeSystem(system->getType()));
  return (NULL);
}

World	*World::removeSystem(const std::string &type)
{
  auto it = std::find_if(this->_systems.begin(), this->_systems.end(),
			 [type] (ISystem *system) -> bool {
			   return (system->getType() == type);
			 });

  if (it == this->_systems.end())
    return (NULL);

  delete *it;
  this->_systems.erase(it);
  return (this);
}

//----- ----- Methods ----- ----- //
void	World::process()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->process(this->_entities);
    });
}
