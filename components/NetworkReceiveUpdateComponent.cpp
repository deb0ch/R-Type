#include "NetworkReceiveUpdateComponent.hh"

NetworkReceiveUpdateComponent::NetworkReceiveUpdateComponent(unsigned int remote_id,
							     unsigned int packet_num)
  : AComponent("NetworkReceiveUpdateComponent")
{
  this->_remote_id = remote_id;
  this->_packet_num = packet_num;
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
