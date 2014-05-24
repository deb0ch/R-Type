#include "NetworkSendUpdateComponent.hh"

NetworkSendUpdateComponent::NetworkSendUpdateComponent()
  : ACopyableComponent("NetworkSendUpdateComponent")
{
  this->_packet_number = 0;
}

NetworkSendUpdateComponent::~NetworkSendUpdateComponent()
{}

unsigned int	NetworkSendUpdateComponent::getPacketNumber() const
{
  return (this->_packet_number);
}

void	NetworkSendUpdateComponent::increasePacketNumber()
{
  ++this->_packet_number;
}

void NetworkSendUpdateComponent::serialize(IBuffer &) const
{}

void NetworkSendUpdateComponent::unserialize(IBuffer &)
{}
