#include "DisconnectPlayerEvent.hh"

DisconnectPlayerEvent::DisconnectPlayerEvent(unsigned int hash) : AEvent("DisconnectPlayerEvent"), _hash(hash)
{}

DisconnectPlayerEvent::~DisconnectPlayerEvent()
{}

unsigned int DisconnectPlayerEvent::getRemoteId() const
{
  return this->_hash;
}
