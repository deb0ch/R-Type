#include <iostream>
#include "NetworkSendUpdateSystem.hh"
#include "ISerializableComponent.hh"
#include "IComponent.hh"
#include "NetworkSendUpdateComponent.hh"
#include "NetworkBuffer.hh"

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
    this->_world->getSharedObject< std::vector< NetworkBuffer * > >("LeChevalCestTropGenial");
}

void				NetworkSendUpdateSystem::start()
{
  this->_world->setSharedObject("LeChevalCestTropGenial", new std::vector<NetworkBuffer *>());
}

void				NetworkSendUpdateSystem::serializeComponents(Entity *entity,
									     NetworkBuffer &buffer)
{
  ISerializableComponent	*serializable_component;
  IComponent			*component;
  std::hash<std::string>	hash;

  for (auto it = this->_component_to_send.begin(); it != this->_component_to_send.end(); ++it)
    {
      if ((serializable_component = entity->getComponent<ISerializableComponent>(*it)) &&
	  (component = dynamic_cast<IComponent *>(serializable_component)))
	{
	  buffer << static_cast<std::size_t>(hash(component->getType()));
	  std::cout << "sended: " << hash(component->getType()) << std::endl;
	  serializable_component->serialize(buffer);
	}
    }
}

void				NetworkSendUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkSendUpdateComponent	*network_component;
  NetworkBuffer			*buffer = new NetworkBuffer();

  network_component = entity->getComponent<NetworkSendUpdateComponent>("NetworkSendUpdateComponent");
  *buffer << static_cast<char>(ENTITY_UPDATE);
  *buffer << entity->_id;
  *buffer << network_component->getPacketNumber();
  *buffer << static_cast<char>(1);
  this->serializeComponents(entity, *buffer);
  network_component->increasePacketNumber();
  this->_packets_sended->push_back(buffer);
  // Send buffer here
}
