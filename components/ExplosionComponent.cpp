#include "ExplosionComponent.hh"

ExplosionComponent::ExplosionComponent(const std::string &name, float offsetX, float offsetY)
	: ACopyableComponent("ExplosionComponent")
{
	this->_explosionEntityName = name;
	this->_offsetX = offsetX;
	this->_offsetY = offsetY;
}

ExplosionComponent::~ExplosionComponent()
{}

const std::string &ExplosionComponent::getExplosionEntityName() const
{
	return (this->_explosionEntityName);
}

float ExplosionComponent::getOffsetX() const
{
	return (this->_offsetX);
}

float ExplosionComponent::getOffsetY() const
{
	return (this->_offsetY);
}

void ExplosionComponent::serialize(IBuffer &) const
{}

void ExplosionComponent::unserialize(IBuffer &)
{}
