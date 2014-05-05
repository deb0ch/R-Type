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

Entity	*World::createEntity()
{
  Entity	*res;

  res = new Entity();
  res->_id = this->_nextEntityID++;
  return (res);
}

//----- ----- Setters ----- ----- //

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

//----- ----- Methods ----- ----- //
void	World::process(const float delta)
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this, delta] (ISystem *system) -> void {
      system->process(this->_entities, delta);
    });
}

void	World::start()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->start();
    });
}

void	World::pause()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->pause();
    });
}

void	World::resume()
{
  std::for_each(this->_systems.begin(), this->_systems.end(), [this] (ISystem *system) -> void {
      system->resume();
    });
}

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

IComponent	*World::createComponent(std::size_t type) const
{
  return (this->_component_factory.create(type));
}

IComponent	*World::createComponent(const std::string &type) const
{
  std::hash<std::string> hash;

  std::cout << "alzejazlje: " << hash(type) << std::endl;
  return (this->_component_factory.create(hash(type)));
}

void		World::registerComponent(const IComponent *component)
{
  std::hash<std::string> hash;

  if (!component)
    return ;
  this->_component_factory.add(hash(component->getType()), component);
}
