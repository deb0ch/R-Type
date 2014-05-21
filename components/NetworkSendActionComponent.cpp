#include "NetworkSendActionComponent.hh"

NetworkSendActionComponent::NetworkSendActionComponent(unsigned int id)
  : AComponent<NetworkSendActionComponent>("NetworkSendActionComponent")
{
  this->_packet_number = 0;
  this->_remote_id = id;
}

NetworkSendActionComponent::~NetworkSendActionComponent()
{}

unsigned int NetworkSendActionComponent::getPacketNumber() const
{
  return this->_packet_number;
}

void NetworkSendActionComponent::increasePacketNumber()
{
  ++this->_packet_number;
}

unsigned int	NetworkSendActionComponent::getRemoteId() const
{
  return this->_remote_id;
}

void		NetworkSendActionComponent::setRemoteId(unsigned int id)
{
  this->_remote_id = id;
}

void NetworkSendActionComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_remote_id;
}

void NetworkSendActionComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_remote_id;
}
