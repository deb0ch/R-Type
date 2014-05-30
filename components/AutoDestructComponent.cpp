#include "AutoDestructComponent.hh"

AutoDestructComponent::AutoDestructComponent(unsigned long delay) : ACopyableComponent("AutoDestructComponent")
{
  this->_delay = delay;
  this->_tick = 0;
}

AutoDestructComponent::~AutoDestructComponent(){
}

unsigned long AutoDestructComponent::getDelay() const {
  return this->_delay;
}
unsigned long AutoDestructComponent::getTick() const {
  return this->_tick;
}

void AutoDestructComponent::setDelay(unsigned long delay) {
  this->_delay = delay;
}

void AutoDestructComponent::setTick(unsigned long tick) {
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
    this->_delay = std::stoul(lastline.substr(6));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"");
}

void	AutoDestructComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "delay=" << this->_delay << std::endl;
}
