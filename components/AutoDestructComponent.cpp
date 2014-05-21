#include "AutoDestructComponent.hh"

AutoDestructComponent::AutoDestructComponent(unsigned long delay) : AComponent("AutoDestructComponent")
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
