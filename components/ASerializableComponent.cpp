#include "ASerializableComponent.hh"
#include "Hash.hh"

ASerializableComponent::ASerializableComponent(const std::string &type)
  : AComponent(type), _sendUpdate(true)
{}

void	ASerializableComponent::networkSerialize(Remote *, IBuffer &buffer) const
{
  if (!this->_sendUpdate)
    buffer << static_cast<unsigned long>(0);
  buffer << Hash()(this->getType());
  this->serialize(buffer);
}

ASerializableComponent	*ASerializableComponent::sendUpdate(bool value)
{
  this->_sendUpdate = value;
  return this;
}
