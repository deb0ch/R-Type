#include "AutoDestructComponent.hh"

AutoDestructComponent::AutoDestructComponent(float delay) : ACopyableComponent("AutoDestructComponent")
{
  this->_delay = delay;
  this->_tick = 0;
}

AutoDestructComponent::~AutoDestructComponent()
{}

float AutoDestructComponent::getDelay() const
{
  return this->_delay;
}

float AutoDestructComponent::getTick() const
{
  return this->_tick;
}

void AutoDestructComponent::setDelay(float delay)
{
  this->_delay = delay;
}

void AutoDestructComponent::setTick(float tick)
{
  this->_tick = tick;
}

void AutoDestructComponent::serialize(IBuffer &) const
{}

void AutoDestructComponent::unserialize(IBuffer &)
{}

void	AutoDestructComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("delay=.+")))
    this->_delay = std::stof(lastline.substr(6));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	AutoDestructComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "delay=" << this->_delay << std::endl;
}
