#include	<algorithm>

#include	"VectorDeleter.hpp"
#include	"World.hh"
#include	"Hash.hh"

//----- ----- Constructors ----- ----- //
World::World()
{
  this->_nextEntityID = 1;
  this->_initialized = false;
}

World::World(const World& ref)
{
  this->_entities = ref._entities;
  this->_systems = ref._systems;
  this->_initialized = ref._initialized;
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

/**
 * Create and return a new Entity and increment the nextEntityID.
 * The returned Entity is not added to the World.
 */
Entity	*World::createEntity()
{
  Entity	*res;

  res = new Entity();
  res->_id = this->_nextEntityID++;
  return (res);
}

//----- ----- Setters ----- ----- //

/**
 * Add an Entity into the World and change the nextEntityID if the entity has brought a bigger ID.
 * @todo Prevent adding an Entity with an ID that already is in the World.
 */
World	*World::addEntity(Entity *entity)
{
  this->_entities.push_back(entity);
  if (entity->_id >= this->_nextEntityID)
    _nextEntityID = entity->_id + 1;
  return (this);
}

/**
 * Add a System into the World and sort the vector according to the systems priority..
 * @todo Prevent adding a System that already exists in the World.
 */
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
    this->removeEntity(entity->_id);
  return (this);
}

World	*World::removeEntity(unsigned long id)
{
  auto it = std::find_if(this->_entities.begin(), this->_entities.end(),
			 [id] (Entity *entity) -> bool {
			   return (entity->_id == id);
			 });

  if (it == this->_entities.end())
    return (this);

  delete *it;
  this->_entities.erase(it);
  return (this);
}

World	*World::removeSystem(ISystem *system)
{
  if (system)
    this->removeSystem(system->getType());
  return (this);
}

World	*World::removeSystem(const std::string &type)
{
  auto it = std::find_if(this->_systems.begin(), this->_systems.end(),
			 [type] (ISystem *system) -> bool {
			   return (system->getType() == type);
			 });

  if (it == this->_systems.end())
    return (this);

  delete *it;
  this->_systems.erase(it);
  return (this);
}

std::vector<Entity *> &World::getEntities()
{
  return (this->_entities);
}

Entity		*World::getEntity(unsigned long id)
{
  auto it = std::find_if(this->_entities.begin(), this->_entities.end(),
			 [id] (Entity *entity) -> bool {
			   return (entity->_id == id);
			 });

  if (it == this->_entities.end())
    return (NULL);

  return (*it);
}

//----- ----- Methods ----- ----- //

/**
 * Call the ASystem::process() method of each System, passing all the entities to them.
 * @todo Throw an exception if the World is paused or stopped or not initialized.
 */
void	World::process(const float delta)
{
  if (!this->_initialized)
    this->init();
  std::for_each(this->_systems.begin(), this->_systems.end(), [this, delta] (ISystem *system) -> void {
      system->process(this->_entities, delta);
    });
}

/**
 * @todo All the code.
 */
void	World::init()
{
  this->_initialized = true;
  std::for_each(this->_systems.begin(), this->_systems.end(), [] (ISystem *system) -> void {
      system->init();
    });
}

/**
 * @todo Throw an exception if the World is not stopped or not initialized.
 */
void	World::start()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->start();
    });
}

/**
 * @todo Throw an exception if the World is not running.
 */
void	World::pause()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->pause();
    });
}

/**
 * @todo Throw an exception if the World is not paused.
 */
void	World::resume()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->resume();
    });
}

/**
 * @todo Throw an exception if the World is not started.
 */
void	World::stop()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->stop();
    });
}

void		World::sendEvent(IEvent *event)
{
  this->_event_manager.sendEvent(event);
}

bool		World::hasEventHandler(const std::string &type) const
{
  return (this->_event_manager.hasHandler(type));
}
