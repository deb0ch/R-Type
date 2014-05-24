#include "InputChangedEvent.hh"

InputChangedEvent::InputChangedEvent(Entity *e, const std::string &input)
  : AEvent("InputChangedEvent"), _entity(e), _input(input)
{
}

InputChangedEvent::~InputChangedEvent()
{}

const Entity *InputChangedEvent::getEntity() const
{
  return this->_entity;
}

Entity *InputChangedEvent::getEntity()
{
  return this->_entity;
}

const std::string &InputChangedEvent::getInput() const
{
  return this->_input;
}
