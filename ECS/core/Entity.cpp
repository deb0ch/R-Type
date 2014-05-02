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
  this->_components.push_back(component);
  return (this);
}

Entity		*Entity::removeComponent(IComponent *e)
{
  if (e)
    return (this->removeComponent(e->getType()));
  return (NULL);
}

Entity		*Entity::removeComponent(const std::string &type)
{
  auto it = std::find_if(this->_components.begin(), this->_components.end(),
			 [type] (IComponent *component) -> bool {
			   return (component->getType() == type);
			 });

  if (it == this->_components.end())
    return (NULL);

  delete *it;
  this->_components.erase(it);
  return (this);
}

//----- ----- Methods ----- ----- //
IComponent	*Entity::hasComponent(const std::string &type) const
{
  auto iterator = std::find_if(this->_components.begin(), this->_components.end(),
			       [type] (IComponent *component) -> bool {
				 return (component->getType() == type);
			       });

  if (iterator == this->_components.end())
    return (NULL);
  return (*iterator);
}
