#include <algorithm>
#include "Entity.hh"

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
{}

//----- ----- Operators ----- ----- //
Entity&	Entity::operator=(const Entity& ref)
{
  this->_id = ref._id;
  this->_components = ref._components;
  return (*this);
}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
Entity	*Entity::addComponent(IComponent *component)
{
  this->_components.push_back(component);
  return (this);
}

IComponent	*Entity::hasComponent(const std::string &string_type) const
{
  auto iterator = std::find_if(this->_components.begin(), this->_components.end(),
			       [string_type] (IComponent *component) -> bool {
				 if (component->getType() == string_type)
				   return (true);
				 return (false);
			       });

  if (iterator == this->_components.end())
    return (NULL);
  return (*iterator);
}

bool	Entity::removeComponent(IComponent *e)
{
  auto iterator = std::remove(this->_components.begin(), this->_components.end(), e);

  if (iterator == this->_components.end())
    return (false);
  this->_components.erase(iterator, this->_components.end());
  return (true);
}

bool	Entity::removeComponent(const std::string &id)
{
  auto iterator = std::remove_if(this->_components.begin(), this->_components.end(),
				 [id] (IComponent *component) -> bool {
				   return (component->getType() == id);
				 });

  if (iterator == this->_components.end())
    return (false);
  this->_components.erase(iterator, this->_components.end());
  return (true);
}
