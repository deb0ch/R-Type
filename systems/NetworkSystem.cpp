#include <iostream>
#include "NetworkSystem.hh"
#include "ISerializableComponent.hh"

NetworkSystem::NetworkSystem(const std::vector<std::string> &component_to_send) : ASystem("NetworkSystem")
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
  ISerializableComponent	*component;

  for (auto it = this->_component_to_send.begin(); it != this->_component_to_send.end(); ++it)
    {
      component = entity->getComponent<ISerializableComponent>(*it);
      std::cout << "serializing: " << *it << " : " << component->serialize() << std::endl;
    }
}
