#include <iostream>
#include "NetworkSystem.hh"
#include "ASerializableComponent.hh"

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
  ASerializableComponent	*component;
  std::string			buffer;
  std::hash<std::string>	hash;

  for (auto it = this->_component_to_send.begin(); it != this->_component_to_send.end(); ++it)
    {
      if ((component = entity->getComponent<ASerializableComponent>(*it)))
	{
	  buffer += std::to_string(hash(component->getType()));
	  buffer += component->serialize();
	}
    }
  // Send buffer here
}
