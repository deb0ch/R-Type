#include "SyncPos2DComponent.hh"

SyncPos2DComponent::SyncPos2DComponent() : ACopyableComponent("SyncPos2DComponent")
{}

SyncPos2DComponent::~SyncPos2DComponent()
{}

const Pos2DComponent	&SyncPos2DComponent::getSyncPos() const
{
  return this->_sync_pos;
}

// We should never serialize this component
void		SyncPos2DComponent::serialize(IBuffer &buffer) const
{
  this->_sync_pos.serialize(buffer);
}

void		SyncPos2DComponent::unserialize(IBuffer &buffer)
{
  this->_sync_pos.unserialize(buffer);
}
