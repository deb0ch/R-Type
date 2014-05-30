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

void	AutoDestructComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "delay=" << this->_delay << std::endl;
}
