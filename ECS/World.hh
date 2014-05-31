#ifndef WORLD_H_
# define WORLD_H_

# include	<vector>

# include	"Entity.hh"
# include	"ISystem.hh"
# include	"EventManager.hpp"
# include	"Any.hpp"

# define	DEBUG true

/**
 * @brief The primary class of the framework that contains all the entities and the systems.
 * @todo Add two boolean state attributes to keep trace of the start() / stop() and pause() / resume() methods calls.
 * @todo Reflect if init is really usefull.
 */
class		World
{
private:
  std::vector<Entity*>			_entities;
  std::vector<ISystem*>			_systems;
  /** @brief A map of object pointers that can be shared between systems. */
  std::map<std::string, Any>		_shared_objs;
  /** @brief The next Entity::_id that will be attributed when calling createEntity(). */
  unsigned int				_nextEntityID;
  /** An event manager that allows systems to comunicate together. */
  EventManager<ISystem>			_event_manager;
  //Factory<IComponent, std::size_t>	_component_factory;
  bool					_initialized;

public:

  World();
  World(const World&);
  virtual	~World();
  World&	operator=(const World&);

  /**
   * @brief Create a new Entity with an ID that come from the current World.
   * @return A new Entity with an ID already setted.
   */
  Entity	*createEntity();

  /**
   * @brief Add an Entity into the World.
   * @param entity The Entity to add into the World.
   * @return A pointer to the World to concatenate method calls.
   */
  World		*addEntity(Entity *);

  /**
   * @brief Add a System into the World.
   * @param system The System to add into the World.
   * @return A pointer to the World to concatenate method calls.
   */
  World		*addSystem(ISystem *);
  /** @see World::removeEntity(unsigned int id); */
  World		*removeEntity(Entity *);
  World		*removeEntity(unsigned int id);
    /** @see World::removeSystem(const std::string &type) */
  World		*removeSystem(ISystem *);
  World		*removeSystem(const std::string &type);

  ISystem	*getSystem(const std::string &type);

  template <typename T>
  T		*getSystem(const std::string &type)
  {
    ISystem	*system;
    T		*result;

    if (!(system = this->getSystem(type)))
      return (NULL);
    if (!(result = dynamic_cast<T *>(system)))
      {
	std::cerr << "Invalid type" << std::endl; // throw exception
	abort();
      }
    return (result);
  }

  template <typename T>
  World		*addEventHandler(const std::string &type, ISystem *obj,
				 void (T::*handler)(IEvent *))
  {
    this->_event_manager.addHandler(type, obj, static_cast<void (ISystem::*)(IEvent *)>(handler));
    return (this);
  }

  bool		hasEventHandler(const std::string &type) const;
  void		sendEvent(IEvent *event);

  std::vector<Entity *>	&getEntities();
  Entity	*getEntity(unsigned int id);

  void		process(const float delta);
  /** @brief Init all the systems. */
  void		init();
  /** @brief Start all the systems. */
  void		start();
  /** @brief Pause all the systems. */
  void		pause();
  /** @brief Resume all the systems. */
  void		resume();
  /** @brief Stop all the systems. */
  void		stop();

  template <typename T>
  void		setSharedObject(const std::string &type, T *obj)
  {
    auto it = this->_shared_objs.find(type);

    if (it != this->_shared_objs.end())
      it->second = obj;
    else
      {
	this->_shared_objs.insert(std::make_pair(type, Any(obj)));
      }
  }

  template <typename T>
  T		*getSharedObject(const std::string &type)
  {
    auto it = this->_shared_objs.find(type);

    if (it == this->_shared_objs.end())
      return (NULL);
    return (it->second.getValue<T>());
  }
};

#endif /* !WORLD_H_ */
