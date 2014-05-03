#include "ASerializableComponent.hh"

ASerializableComponent::ASerializableComponent(const std::string &type) : AComponent(type)
{}

ASerializableComponent::~ASerializableComponent()
{}

std::string ASerializableComponent::serialize() const
{
  return ("Component not serializable");
}
