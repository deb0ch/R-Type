#include	<algorithm>
#include	"Entity.hh"
#include	"VectorDeleter.hpp"

//----- ----- Constructors ----- ----- //
Entity::Entity()
{}

Entity::Entity(const Entity& ref)
{
  this->_id = ref._id;
  this->_components = ref._components;
}

//----- ----- Destructor ----- ----- //
Entity::~Entity()
{
  std::for_each(this->_components.begin(), this->_components.end(), VectorDeleter<IComponent*>());
}

//----- ----- Operators ----- ----- //
Entity&		Entity::operator=(const Entity& ref)
{
  this->_id = ref._id;
  this->_components = ref._components;
  return (*this);
}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
/**
 * @todo Throw an exception if the component already exists in the Entity.
 */
Entity		*Entity::addComponent(IComponent *component)
{
  if (!component)
    abort();
  if (component && !this->hasComponent(component->getType()))
    this->_components.push_back(component);
  return (this);
}

Entity		*Entity::removeComponent(IComponent *e)
{
  if (e)
    this->removeComponent(e->getType());
  return (this);
}

Entity		*Entity::removeComponent(const std::string &type)
{
  auto it = std::find_if(this->_components.begin(), this->_components.end(),
			 [type] (IComponent *component) -> bool {
			   return (component->getType() == type);
			 });

  if (it == this->_components.end())
    return (this);

  delete *it;
  this->_components.erase(it);
  return (this);
}


Entity		*Entity::removeAllComponent()
{
  std::for_each(this->_components.begin(), this->_components.end(), VectorDeleter<IComponent*>());
  this->_components.clear();
  return (this);
}


Entity		*Entity::removeAllComponentExcept(const IComponent *component)
{
  if (!component)
    return (this);
  return (this->removeAllComponentExcept(component->getType()));
}

Entity		*Entity::removeAllComponentExcept(const std::string &type)
{
  IComponent	*except_component = NULL;

  std::for_each(this->_components.begin(), this->_components.end(),
		[type, &except_component] (IComponent *component) -> void {
		  if (component->getType() != type)
		    delete component;
		  else
		    except_component = component;
		});

  this->_components.clear();
  if (except_component)
    this->addComponent(except_component);
  return (this);
}

//----- ----- Methods ----- ----- //
/**
 * @todo Throw an exception if the component is not found.
 */
IComponent	*Entity::getComponent(const std::string &type) const
{
  auto iterator = std::find_if(this->_components.begin(), this->_components.end(),
			       [type] (IComponent *component) -> bool {
				 return (component->getType() == type);
			       });

  if (iterator == this->_components.end())
    return (NULL);
  return (*iterator);
}

bool		Entity::hasComponent(const std::string &string_type) const
{
  return (this->getComponent(string_type) != NULL);
}
