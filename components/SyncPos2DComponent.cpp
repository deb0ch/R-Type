#include "SyncPos2DComponent.hh"
#include "Pos2DComponent.hh"
#include "NetworkReceiveUpdateComponent.hh"

SyncPos2DComponent::SyncPos2DComponent() : ACopyableComponent("SyncPos2DComponent")
{}

SyncPos2DComponent::~SyncPos2DComponent()
{}

const Pos2DComponent	&SyncPos2DComponent::getSyncPos() const
{
  return this->_sync_pos;
}

Pos2DComponent		&SyncPos2DComponent::getSyncPos()
{
  return this->_sync_pos;
}

void		SyncPos2DComponent::serialize(IBuffer &buffer) const
{
  this->_sync_pos.serialize(buffer);
}

void		SyncPos2DComponent::unserialize(IBuffer &buffer)
{
  this->_sync_pos.unserialize(buffer);
}

float		SyncPos2DComponent::getRatio() const
{
  return this->_ratio;
}

void			SyncPos2DComponent::networkUnserializeCallback(IBuffer &, World *, Entity *entity)
{
  Pos2DComponent	*pos_component;
  NetworkReceiveUpdateComponent *network_comp;

  pos_component = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  network_comp = entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
  if (pos_component && network_comp)
    {
      this->_sync_pos.setX(this->_sync_pos.getX() - pos_component->getX());
      this->_sync_pos.setY(this->_sync_pos.getY() - pos_component->getY());
      if (network_comp->getUpdateRate() != 0)
	this->_ratio = (1.f / network_comp->getUpdateRate()) * 8;
      else
	this->_ratio = 1.f;
    }
  else
    {
      this->_sync_pos.setX(0);
      this->_sync_pos.setY(0);
    }
}
