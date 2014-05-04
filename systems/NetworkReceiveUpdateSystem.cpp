#include "NetworkReceiveUpdateSystem.hh"
#include "NetworkReceiveUpdateComponent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "Serializer.hpp"
#include "ISerializableComponent.hh"

NetworkReceiveUpdateSystem::NetworkReceiveUpdateSystem() : ASystem("NetworkReceiveUpdateSystem")
{}

NetworkReceiveUpdateSystem::~NetworkReceiveUpdateSystem()
{}

bool				NetworkReceiveUpdateSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("NetworkReceiveUpdateComponent"))
    return (true);
  return (false);
}

void				NetworkReceiveUpdateSystem::beforeProcess()
{
  auto				tmp =
    this->_world->getSharedObject< std::vector< std::pair<const char *, int> > >("LeChevalCestTropGenial");

  if (tmp)
    {
      this->_packets_to_apply = *tmp;
    }
}

void				NetworkReceiveUpdateSystem::afterProcess()
{
  unsigned int			id_entity;
  unsigned int			num_packet;
  Entity			*entity;
  int				lenght_read;

  for (auto it = this->_packets_to_apply.begin(); it != this->_packets_to_apply.end(); ++it)
    {
      if (it->second >= 1 && *it->first == ENTITY_UPDATE) // setup a try{}catch here for unserialize
	{
	  lenght_read = this->getEntityInfos(it->first, it->second, id_entity, num_packet);
	  entity = this->_world->createEntity();
	  entity->addComponent(new NetworkReceiveUpdateComponent(id_entity, num_packet));
	  this->updateEntity(entity, it->first + lenght_read, it->second - lenght_read);
	  this->_world->addEntity(entity);
	  it = this->_packets_to_apply.erase(it);
	}
    }
}

int				NetworkReceiveUpdateSystem::unserializeComponent(Entity *entity,
										 const char *buffer,
										 int lenght)
{
  std::size_t			component_hash;
  int				lenght_read;
  IComponent			*new_component;
  ISerializableComponent	*serializable_component;

  lenght_read = 0;
  lenght_read += Serializer<std::size_t>::unserialize(buffer + lenght_read,
						      lenght - lenght_read, component_hash);
  new_component = this->_world->createComponent(component_hash);
  if (!(serializable_component = dynamic_cast<ISerializableComponent *>(new_component)))
    {
      std::cerr << "Received a no serializable component" << std::endl;
      throw 1;
    }
  lenght_read += serializable_component->unserialize(buffer + lenght_read, lenght - lenght_read);
  return (lenght_read);
}

void				NetworkReceiveUpdateSystem::updateEntity(Entity *entity,
									 const char *buffer,
									 int lenght)
{
  int				lenght_read;

  lenght_read = 0;
  entity->removeAllComponentExcept("NetworkReceiveUpdateComponent");
  while (lenght_read < lenght)
    {
      lenght_read += this->unserializeComponent(entity, buffer + lenght_read, lenght - lenght_read);
    }
}

int				NetworkReceiveUpdateSystem::getEntityInfos(const char *buffer,
									   int lenght,
									   unsigned int &id_entity,
									   unsigned int &num_packet)
{
  int				lenght_read;

  lenght_read = 1;
  lenght_read += Serializer<unsigned int>::unserialize(buffer + lenght_read,
						       lenght - lenght_read, id_entity);
  lenght_read += Serializer<unsigned int>::unserialize(buffer + lenght_read,
						       lenght - lenght_read, num_packet);
  lenght_read++;	// force byte
  return (lenght_read);
}


void				NetworkReceiveUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkReceiveUpdateComponent	*receive_component;
  int				lenght_read;
  unsigned int			id_entity;
  unsigned int			num_packet;

  receive_component = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
  for (auto it = this->_packets_to_apply.begin(); it != this->_packets_to_apply.end(); ++it)
    {
      if (it->second >= 1 && *it->first == ENTITY_UPDATE) // setup a try{}catch here for unserialize
	{
	  this->getEntityInfos(it->first, it->second, id_entity, num_packet);
	  if (num_packet > receive_component->getPacketNum())
	    {
	      this->updateEntity(entity, it->first + lenght_read, it->second - lenght_read);
	      receive_component->setPacketNum(num_packet);
	    }
	  it = this->_packets_to_apply.erase(it);
	}
    }
}
