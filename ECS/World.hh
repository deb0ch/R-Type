#ifndef WORLD_H_
# define WORLD_H_

# include	<vector>

# include	"Entity.hh"
# include	"ISystem.hh"
# include	"EventManager.hpp"
# include	"Any.hpp"

class		World
{
private:
  std::vector<Entity*>		_entities;
  std::vector<ISystem*>		_systems;
  std::map<std::string, Any>	_shared_objs;
  unsigned long			_nextEntityID;
  EventManager<ISystem>		_event_manager;

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

  template <typename T>
  World		*addEventHandler(const std::string &type, ISystem *obj,
				 void (T::*handler)(IEvent *))
  {
    this->_event_manager.addHandler(type, obj, static_cast<void (ISystem::*)(IEvent *)>(handler));
    return (this);
  }

  bool		hasEventHandler(const std::string &type) const;
  void		sendEvent(IEvent *event);

  std::vector<Entity *> &getEntities();

  void		process(const float delta);
  void		start();
  void		pause();
  void		resume();
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
