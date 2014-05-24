#include "ASerializableComponent.hh"
#include "Hash.hh"

ASerializableComponent::ASerializableComponent(const std::string &type)
  : AComponent(type), _sendUpdate(true), _send(true)
{}

void	ASerializableComponent::networkSerialize(Remote *, IBuffer &buffer, bool force_send) const
{
  if (this->_send || force_send)
    {
      if (!this->_sendUpdate)
	buffer << static_cast<unsigned long>(0);
      buffer << Hash()(this->getType());
      this->serialize(buffer);
    }
}

ASerializableComponent	*ASerializableComponent::setNetworkSendUpdate(bool value)
{
  this->_sendUpdate = value;
  return this;
}

ASerializableComponent *ASerializableComponent::setNetworkSend(bool value)
{
  this->_send = value;
  return this;
}

IComponent		*ASerializableComponent::clone() const
{
  return (this->cloneSerializable());
}
