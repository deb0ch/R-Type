#include "NetworkReceiveUpdateSystem.hh"
#include "NetworkReceiveUpdateComponent.hh"
#include "NetworkSendUpdateSystem.hh"
#include "Serializer.hpp"
#include "ISerializableComponent.hh"

NetworkReceiveUpdateSystem::NetworkReceiveUpdateSystem() : ASystem("NetworkReceiveUpdateSystem")
{
  i = 0;
}

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
    this->_packets_to_apply = tmp;
}

void				NetworkReceiveUpdateSystem::afterProcess()
{
  unsigned int			id_entity;
  unsigned int			num_packet;
  Entity			*entity;
  int				lenght_read;

  if (i < 50)
    {
      i++;
      return ;
    }
  i = 0;
  auto it = this->_packets_to_apply->begin();
  while (it != this->_packets_to_apply->end())
    {
      if (it->second >= 1 && *it->first == ENTITY_UPDATE) // setup a try{}catch here for unserialize
	{
	  lenght_read = 1;
	  lenght_read += this->getEntityInfos(it->first + lenght_read, it->second - lenght_read,
					      id_entity, num_packet);
	  entity = this->_world->createEntity();
	  entity->addComponent(new NetworkReceiveUpdateComponent(id_entity, num_packet));
	  std::cout << "-------------------- CREATE ENTITY -----------------------" << std::endl;
	  this->updateEntity(entity, it->first + lenght_read, it->second - lenght_read);
	  this->_world->addEntity(entity);
	  it = this->_packets_to_apply->erase(it);
	}
      else
	++it;
    }
}

void				NetworkReceiveUpdateSystem::processEntity(Entity *entity, const float)
{
  NetworkReceiveUpdateComponent	*receive_component;
  int				lenght_read;
  unsigned int			id_entity;
  unsigned int			num_packet;

  if (i < 50)
    return ;
  receive_component = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
  auto it = this->_packets_to_apply->begin();
  while (it != this->_packets_to_apply->end())
    {
      if (it->second >= 1 && *it->first == ENTITY_UPDATE) // setup a try{}catch here for unserialize
	{
	  lenght_read = 1;
	  lenght_read += this->getEntityInfos(it->first + lenght_read, it->second - lenght_read,
					      id_entity, num_packet);
	  if (id_entity == receive_component->getRemoteID())
	    {
	      if (num_packet > receive_component->getPacketNum())
		{
		  std::cout << "-------------------- UPDATING ENTITY -----------------------" << std::endl;
		  this->updateEntity(entity, it->first + lenght_read, it->second - lenght_read);
		  receive_component->setPacketNum(num_packet);
		}
	      it = this->_packets_to_apply->erase(it);
	    }
	  else
	    ++it;
	}
      else
	++it;
    }
}


// -------------- Private functions --------------

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
  std::cout << component_hash << std::endl;
  new_component = this->_world->createComponent(component_hash);
  std::cout << new_component << std::endl;
  if (!(serializable_component = dynamic_cast<ISerializableComponent *>(new_component)))
    {
      std::cerr << "Received a no serializable component" << std::endl;
      throw 1;
    }
  lenght_read += serializable_component->unserialize(buffer + lenght_read, lenght - lenght_read);
  entity->addComponent(new_component);
  return (lenght_read);
}

void				NetworkReceiveUpdateSystem::updateEntity(Entity *entity,
									 const char *buffer,
									 int lenght)
{
  int				lenght_read;

  lenght_read = 0;
  auto it = entity->_components.begin();
  while (it != entity->_components.end())
    {
      if (dynamic_cast<ISerializableComponent *>(*it) != NULL) // We delete all serializable component
	{
	  delete *it;
	  it = entity->_components.erase(it);
	}
      else
	++it;
    }
  while (lenght_read < lenght)
    {
      lenght_read += this->unserializeComponent(entity, buffer + lenght_read, lenght - lenght_read);
      std::for_each(entity->_components.begin(), entity->_components.end(), [] (IComponent *component) -> void {
	  std::cout << component->getType() << std::endl;
	});
    }
}

int				NetworkReceiveUpdateSystem::getEntityInfos(const char *buffer,
									   int lenght,
									   unsigned int &id_entity,
									   unsigned int &num_packet)
{
  int				lenght_read;

  lenght_read = 0;
  lenght_read += Serializer<unsigned int>::unserialize(buffer + lenght_read,
						       lenght - lenght_read, id_entity);
  lenght_read += Serializer<unsigned int>::unserialize(buffer + lenght_read,
						       lenght - lenght_read, num_packet);
  ++lenght_read;	// force byte -- may change
  return (lenght_read);
}
