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
Entity		*Entity::addComponent(IComponent *component)
{
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

//----- ----- Methods ----- ----- //
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
