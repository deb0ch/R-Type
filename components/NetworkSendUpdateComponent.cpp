#include "NetworkSendUpdateComponent.hh"

NetworkSendUpdateComponent::NetworkSendUpdateComponent(const float update_rate)
  : ACopyableComponent("NetworkSendUpdateComponent")
{
  this->_packet_number = 0;
  this->_update_rate = update_rate;
  this->_last_update_delay = 0;
  this->_first_update = true;
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

float	NetworkSendUpdateComponent::getUpdateRate() const
{
  return this->_update_rate;
}

NetworkSendUpdateComponent	*NetworkSendUpdateComponent::setUpdateRate(const float value)
{
  this->_update_rate = value;
  return this;
}

void		NetworkSendUpdateComponent::addLastUpdateDelay(const float value)
{
  this->_last_update_delay += value;
}

bool		NetworkSendUpdateComponent::canSend()
{
  if (this->_first_update || this->_last_update_delay >= this->_update_rate)
    return true;
  return false;
}

void		NetworkSendUpdateComponent::resetLastUpdateDelay()
{
  this->_first_update = false;
  this->_last_update_delay = 0;
}

void NetworkSendUpdateComponent::serialize(IBuffer &) const
{}

void NetworkSendUpdateComponent::unserialize(IBuffer &)
{}

void	NetworkSendUpdateComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("update_rate=.+")))
    this->_update_rate = std::stof(lastline.substr(12));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	NetworkSendUpdateComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "update_rate=" << this->_update_rate << std::endl;
}
