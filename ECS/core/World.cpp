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
  return (this);
}

//----- ----- Methods ----- ----- //
void	World::process()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this](ISystem *system) -> void {
      system->process(this->_entities);
    });
}
