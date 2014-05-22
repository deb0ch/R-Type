#include "ExplosionComponent.hh"

ExplosionComponent::ExplosionComponent(const std::string &name)
	: AComponent("ExplosionComponent")
{
	this->_explosionEntityName = name;
}

ExplosionComponent::~ExplosionComponent()
{}

const std::string &ExplosionComponent::getExplosionEntityName() const
{
	return (this->_explosionEntityName);
}