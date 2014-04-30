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

Entity	*World::addEntity(Entity *entity)
{
  this->_entities.push_back(entity);
  if (entity->_id >= this->_nextEntityID)
    _nextEntityID = entity->_id + 1;
  return (entity);
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
  this->_entities.erase(std::remove(this->_entities.begin(), this->_entities.end(), entity), this->_entities.end());
  return (this);
}

World	*World::removeSystem(ISystem *system)
{
  this->_systems.erase(std::remove(this->_systems.begin(), this->_systems.end(), system), this->_systems.end());
  return (this);
}

//----- ----- Methods ----- ----- //
void	World::process()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->process(this->_entities);
    });
}
