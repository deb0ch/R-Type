#include "NewPlayerEvent.hh"


NewPlayerEvent::NewPlayerEvent(unsigned int hash) : AEvent("NewPlayerEvent"), _hash(hash)
{}

NewPlayerEvent::~NewPlayerEvent()
{}

unsigned int NewPlayerEvent::getRemoteId() const
{
  return this->_hash;
}
