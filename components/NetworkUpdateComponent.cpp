#include "NetworkUpdateComponent.hh"

NetworkUpdateComponent::NetworkUpdateComponent() : AComponent("NetworkUpdateComponent")
{
  this->_packet_number = 0;
}

NetworkUpdateComponent::~NetworkUpdateComponent()
{}

int	NetworkUpdateComponent::getPacketNumber() const
{
  return (this->_packet_number);
}

void	NetworkUpdateComponent::increasePacketNumber()
{
  ++this->_packet_number;
}
