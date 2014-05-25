#include "NetworkReceiveUpdateComponent.hh"

NetworkReceiveUpdateComponent::NetworkReceiveUpdateComponent(unsigned int remote_id,
							     unsigned int packet_num)
  : ACopyableComponent("NetworkReceiveUpdateComponent")
{
  this->_remote_id = remote_id;
  this->_packet_num = packet_num;
  this->_last_update = 0;
  this->_previous_update_time = 0;
}

NetworkReceiveUpdateComponent::~NetworkReceiveUpdateComponent()
{}

unsigned int	NetworkReceiveUpdateComponent::getRemoteID() const
{
  return (this->_remote_id);
}

void		NetworkReceiveUpdateComponent::setRemoteID(unsigned int id)
{
  this->_remote_id = id;
}

unsigned int	NetworkReceiveUpdateComponent::getPacketNum() const
{
  return (this->_packet_num);
}

void		NetworkReceiveUpdateComponent::setPacketNum(unsigned int num)
{
  this->_packet_num = num;
}

void		NetworkReceiveUpdateComponent::serialize(IBuffer &) const
{}

void		NetworkReceiveUpdateComponent::unserialize(IBuffer &)
{}

void		NetworkReceiveUpdateComponent::resetLastUpdate()
{
  this->_previous_update_time = this->_last_update;
  this->_last_update = 0;
}

void		NetworkReceiveUpdateComponent::increaseLastUpdate()
{
  ++this->_last_update;
}

unsigned int	NetworkReceiveUpdateComponent::getLastUpdate() const
{
  return this->_last_update;
}

unsigned int	NetworkReceiveUpdateComponent::getPreviousUpdateTime() const
{
  return this->_previous_update_time;
}
