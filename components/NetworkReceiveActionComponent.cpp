#include "NetworkReceiveActionComponent.hh"

NetworkReceiveActionComponent::NetworkReceiveActionComponent(unsigned int packet_num)
  : AComponent("NetworkReceiveActionComponent")
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
