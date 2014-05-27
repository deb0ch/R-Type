#include <algorithm>
#include "ASerializableComponent.hh"
#include "Hash.hh"

ASerializableComponent::ASerializableComponent(const std::string &type)
  : AComponent(type), _can_send_update(true), _can_send(true)
{}

void	ASerializableComponent::networkSerialize(Remote *remote, IBuffer &buffer, bool force_send) const
{
  if (this->canSend(remote->getPrivateHash()) || force_send)
    {
      if (!this->canSendUpdate(remote->getPrivateHash()))
	buffer << static_cast<hash_t>(0);
      buffer << Hash()(this->getType());
      this->serialize(buffer);
      this->additionalNetworkSerialize(buffer);
    }
}

void	ASerializableComponent::networkUnSerialize(IBuffer &buffer, World *world, Entity *entity)
{
  this->unserialize(buffer);
  this->networkUnserializeCallback(buffer, world, entity);
}

void	ASerializableComponent::networkUnserializeCallback(IBuffer &, World *, Entity *)
{}

void	ASerializableComponent::additionalNetworkSerialize(IBuffer &) const
{}

ASerializableComponent	*ASerializableComponent::setNetworkSendUpdateException(unsigned int id)
{
  this->_exception_send_update.push_back(id);
  return this;
}

ASerializableComponent *ASerializableComponent::setNetworkSendException(unsigned int id)
{
  this->_exception_send.push_back(id);
  return this;
}

ASerializableComponent	*ASerializableComponent::setNetworkCanSendUpdate(bool value)
{
  this->_can_send_update = value;
  return this;
}

ASerializableComponent	*ASerializableComponent::setNetworkCanSend(bool value)
{
  this->_can_send = value;
  return this;
}

IComponent		*ASerializableComponent::clone() const
{
  return (this->cloneSerializable());
}

bool			ASerializableComponent::canSend(unsigned int remote_id) const
{
  if (std::any_of(this->_exception_send.begin(), this->_exception_send.end(),
		  [&remote_id] (unsigned int id)
		  {
		    return (remote_id == id);
		  }))
    return (!this->_can_send);
  return (this->_can_send);
}

bool			ASerializableComponent::canSendUpdate(unsigned int remote_id) const
{
  if (std::any_of(this->_exception_send_update.begin(), this->_exception_send_update.end(),
		  [&remote_id] (unsigned int id)
		  {
		    return (remote_id == id);
		  }))
    return (!this->_can_send_update);
  return (this->_can_send_update);
}
