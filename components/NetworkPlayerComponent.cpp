#include <algorithm>
#include "NetworkPlayerComponent.hh"
#include "Hash.hh"

const std::vector<std::string> NetworkPlayerComponent::_non_update_component =
  {"Pos2DComponent", "Speed2DComponent"};

NetworkPlayerComponent::NetworkPlayerComponent(unsigned int hash, const std::string &entity_name)
  : ASerializableComponent("NetworkPlayerComponent")
{
  this->_remote_hash = hash;
  this->_can_respawn = true;
  this->_entity_name = entity_name;
}

NetworkPlayerComponent::~NetworkPlayerComponent()
{}

NetworkPlayerComponent::NetworkPlayerComponent(const NetworkPlayerComponent &e)
  : NetworkPlayerComponent()
{
  this->operator=(e);
}

NetworkPlayerComponent &NetworkPlayerComponent::operator=(const NetworkPlayerComponent &e)
{
  if (this != &e)
    {
      this->_remote_hash = e._remote_hash;
      std::for_each(this->_components.begin(), this->_components.end(),
		    [] (ASerializableComponent *comp)
		    {
		      delete comp;
		    });
      this->_components.clear();
      std::for_each(e._components.begin(), e._components.end(),
		    [this] (const ASerializableComponent *comp)
		    {
		      this->_components.push_back(comp->cloneSerializable());
		    });
    }
  return (*this);
}

ASerializableComponent *NetworkPlayerComponent::cloneSerializable() const
{
  return (new NetworkPlayerComponent(*this));
}

NetworkPlayerComponent		*NetworkPlayerComponent::setRemoteId(unsigned int hash)
{
  this->_remote_hash = hash;
  return this;
}

unsigned int			NetworkPlayerComponent::getRemoteId() const
{
  return this->_remote_hash;
}

void			NetworkPlayerComponent::serialize(IBuffer &) const
{
}

void			NetworkPlayerComponent::unserialize(IBuffer &)
{
}

void			NetworkPlayerComponent::setRespawn(bool value)
{
  this->_can_respawn = value;
}

bool			NetworkPlayerComponent::canRespawn() const
{
  return this->_can_respawn;
}

void			NetworkPlayerComponent::networkSerialize(Remote *remote, IBuffer &buffer,
								 bool send_force) const
{
  if (this->canSend(remote->getPrivateHash()) || send_force)
    {
      if (remote->getPrivateHash() == this->_remote_hash)
	{
	  std::for_each(this->_components.begin(), this->_components.end(),
			[&buffer, &remote] (const ASerializableComponent *comp)
			{
			  comp->networkSerialize(remote, buffer, true);
			});
	}
    }
}

NetworkPlayerComponent	*NetworkPlayerComponent::addPlayerComponent(ASerializableComponent *component)
{
  if (component)
    {
      component->setNetworkCanSend(false);
      component->setNetworkSendException(this->_remote_hash);
      if (std::find(this->_non_update_component.begin(),
		    this->_non_update_component.end(),
		    component->getType()) != this->_non_update_component.end())
	component->setNetworkSendUpdateException(this->_remote_hash);
      this->_components.push_back(component);
    }
  return this;
}

void	NetworkPlayerComponent::serializeFromFile(std::ofstream &, unsigned char) const
{}

const std::string	&NetworkPlayerComponent::getEntityName() const
{
  return this->_entity_name;
}
