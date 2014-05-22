#include "ASerializableComponent.hh"
#include "Hash.hh"

void	ASerializableComponent::networkSerialize(Remote *, IBuffer &buffer) const
{
  buffer << Hash()(this->getType());
  this->serialize(buffer);
}
