#include <iostream>
#include "NetworkSystem.hh"
#include "ISerializableComponent.hh"
#include "IComponent.hh"
#include "Serializer.hpp"
#include "NetworkUpdateComponent.hh"

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

int				NetworkSystem::serializeComponents(Entity *entity, char *buffer,
								   int buffer_size)
{
  int				lenght_written;
  ISerializableComponent	*serializable_component;
  IComponent			*component;
  std::hash<std::string>	hash;

  lenght_written = 0;
  for (auto it = this->_component_to_send.begin(); it != this->_component_to_send.end(); ++it)
    {
      if ((serializable_component = entity->getComponent<ISerializableComponent>(*it)) &&
	  (component = dynamic_cast<IComponent *>(serializable_component)))
	{
	  lenght_written += Serializer<size_t>::serialize(buffer + lenght_written,
							  buffer_size - lenght_written,
							  hash(component->getType()));
	  lenght_written += serializable_component->serialize(buffer + lenght_written,
							      buffer_size - lenght_written);
	}
    }
  return (lenght_written);
}

void				NetworkSystem::processEntity(Entity *entity, const float)
{
  NetworkUpdateComponent	*network_component;
  char				buffer[this->_buffer_size];
  int				lenght_written;

  network_component = entity->getComponent<NetworkUpdateComponent>("NetworkUpdateComponent");
  *buffer = ENTITY_UPDATE;
  lenght_written = 1;
  lenght_written += Serializer<int>::serialize(buffer + lenght_written,
					       this->_buffer_size - lenght_written,
					       entity->_id);
  lenght_written += Serializer<int>::serialize(buffer + lenght_written,
					       this->_buffer_size - lenght_written,
					       network_component->getPacketNumber());
  buffer[lenght_written++] = 1;
  lenght_written += this->serializeComponents(entity, buffer + lenght_written,
					      this->_buffer_size - lenght_written);
  network_component->increasePacketNumber();
  // Send buffer here
}
