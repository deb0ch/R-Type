#include <iostream>
#include "NetworkSystem.hh"
#include "ISerializableComponent.hh"
#include "IComponent.hh"

NetworkSystem::NetworkSystem(const std::vector<std::string> &component_to_send)
  : ASystem("NetworkSystem")
{
  this->_component_to_send = component_to_send;
}

NetworkSystem::~NetworkSystem()
{}

bool				NetworkSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("NetworkUpdateComponent"))
    return (true);
  return (false);
}

void				NetworkSystem::processEntity(Entity *entity, const float)
{
  ISerializableComponent	*serializable_component;
  IComponent			*component;
  std::string			buffer;
  std::hash<std::string>	hash;

  for (auto it = this->_component_to_send.begin(); it != this->_component_to_send.end(); ++it)
    {
      if ((serializable_component = entity->getComponent<ISerializableComponent>(*it)) &&
	  (component = dynamic_cast<IComponent *>(serializable_component)))
	{
	  buffer += std::to_string(hash(component->getType()));
	  buffer += serializable_component->serialize();
	}
    }
  // Send buffer here
}
