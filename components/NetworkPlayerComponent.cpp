#include <algorithm>
#include "NetworkPlayerComponent.hh"
#include "Hash.hh"

NetworkPlayerComponent::NetworkPlayerComponent()
  : ASerializableComponent("NetworkPlayerComponent")
{}

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
      std::for_each(e._components.begin(), e._components.end(),
		    [this] (const ASerializableComponent *comp)
		    {
		      this->_components.push_back(comp->clone());
		    });
    }
  return (*this);
}

ASerializableComponent *NetworkPlayerComponent::clone() const
{
  return (new NetworkPlayerComponent(*this));
}

void			NetworkPlayerComponent::serialize(IBuffer &buffer) const
{
  std::cout << "Not supposed to happen yet" << std::endl;
  throw 1;
}

void			NetworkPlayerComponent::unserialize(IBuffer &buffer)
{
  std::cout << "Not supposed to happen yet" << std::endl;
  throw 1;
}

void			NetworkPlayerComponent::networkSerialize(Remote *remote, IBuffer &buffer) const
{
  if (remote->getPrivateHash() == this->_remote_hash)
    {
      std::for_each(this->_components.begin(), this->_components.end(),
		    [&buffer, &remote] (const ASerializableComponent *comp)
		    {
		      comp->networkSerialize(remote, buffer);
		    });
    }
}
