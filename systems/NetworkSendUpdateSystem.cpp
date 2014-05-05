#include <iostream>
#include "NetworkSendUpdateSystem.hh"
#include "ISerializableComponent.hh"
#include "IComponent.hh"
#include "Serializer.hpp"
#include "NetworkSendUpdateComponent.hh"

NetworkSendUpdateSystem::NetworkSendUpdateSystem(const std::vector<std::string> &component_to_send)
  : ASystem("NetworkSendUpdateSystem")
{
  this->_component_to_send = component_to_send;
}

NetworkSendUpdateSystem::~NetworkSendUpdateSystem()
{}

bool				NetworkSendUpdateSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("NetworkSendUpdateComponent"))
    return (true);
  return (false);
}

void				NetworkSendUpdateSystem::beforeProcess()
{
  this->_packets_sended =
    this->_world->getSharedObject<std::vector< std::pair<const char *, int> > >("LeChevalCestTropGenial");
}

void				NetworkSendUpdateSystem::start()
{
  this->_world->setSharedObject("LeChevalCestTropGenial", new std::vector< std::pair<const char *, int> >());
}

int				NetworkSendUpdateSystem::serializeComponents(Entity *entity, char *buffer,
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
	  lenght_written += Serializer<std::size_t>::serialize(buffer + lenght_written,
							       buffer_size - lenght_written,
							       hash(component->getType()));
	  lenght_written += serializable_component->serialize(buffer + lenght_written,
							      buffer_size - lenght_written);
	}
    }
  return (lenght_written);
}

void				NetworkSendUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkSendUpdateComponent	*network_component;
  char				*buffer = new char[this->_buffer_size];
  int				lenght_written;

  network_component = entity->getComponent<NetworkSendUpdateComponent>("NetworkSendUpdateComponent");
  *buffer = ENTITY_UPDATE;
  lenght_written = 1;
  lenght_written += Serializer<unsigned int>::serialize(buffer + lenght_written,
							this->_buffer_size - lenght_written,
							entity->_id);
  lenght_written += Serializer<unsigned int>::serialize(buffer + lenght_written,
							this->_buffer_size - lenght_written,
							network_component->getPacketNumber());
  buffer[lenght_written++] = 1;
  lenght_written += this->serializeComponents(entity, buffer + lenght_written,
					      this->_buffer_size - lenght_written);
  network_component->increasePacketNumber();
  this->_packets_sended->push_back(std::make_pair(buffer, lenght_written));
  // Send buffer here
}
