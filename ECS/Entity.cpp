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

bool	Entity::hasComponent(const std::string &string_type) const
{
  return (std::any_of(_components.begin(), _components.end(), [string_type](IComponent *component) -> bool {
	if (component->getType() == string_type)
	  return (true);
	return (false);
      }));
}
