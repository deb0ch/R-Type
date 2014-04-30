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
void	Entity::addComponent(IComponent *component)
{
  this->_components.push_back(component);
}
