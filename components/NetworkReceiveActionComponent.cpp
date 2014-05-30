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

void		NetworkReceiveActionComponent::serialize(IBuffer &) const
{}

void		NetworkReceiveActionComponent::unserialize(IBuffer &)
{}

void	NetworkReceiveActionComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("packet_num=.+")))
    this->_packet_num = std::stoul(lastline.substr(11));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	NetworkReceiveActionComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "packet_num=" << this->_packet_num << std::endl;
}
