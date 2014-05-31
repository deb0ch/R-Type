#include "NetworkReceiveUpdateComponent.hh"

NetworkReceiveUpdateComponent::NetworkReceiveUpdateComponent(unsigned int remote_id,
							     unsigned int packet_num,
							     float update_rate)
  : ACopyableComponent("NetworkReceiveUpdateComponent")
{
  this->_remote_id = remote_id;
  this->_packet_num = packet_num;
  this->_update_rate = update_rate;
  this->_last_update = 0;
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

void		NetworkReceiveUpdateComponent::addLastUpdate(const float value)
{
  this->_last_update += value;
}

float		NetworkReceiveUpdateComponent::getLastUpdate() const
{
  return this->_last_update;
}

void		NetworkReceiveUpdateComponent::resetLastUpdate()
{
  this->_last_update = 0;
}

void		NetworkReceiveUpdateComponent::setUpdateRate(const float value)
{
  this->_last_update = value;
}

float		NetworkReceiveUpdateComponent::getUpdateRate() const
{
  return this->_update_rate;
}

void		NetworkReceiveUpdateComponent::serializeFromFile(std::ofstream &, unsigned char) const
{}
