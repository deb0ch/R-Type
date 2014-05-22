#include "NetworkReceiveActionComponent.hh"

NetworkReceiveActionComponent::NetworkReceiveActionComponent(unsigned int packet_num)
  : ACopyableComponent("NetworkReceiveActionComponent")
{
  this->_packet_num = packet_num;
}

NetworkReceiveActionComponent::~NetworkReceiveActionComponent()
{}

unsigned int	NetworkReceiveActionComponent::getPacketNum() const
{
  return (this->_packet_num);
}

void		NetworkReceiveActionComponent::setPacketNum(unsigned int num)
{
  this->_packet_num = num;
}

void		NetworkReceiveActionComponent::serialize(IBuffer &buffer) const
{}

void		NetworkReceiveActionComponent::unserialize(IBuffer &buffer)
{}
