#include "LifeComponent.hh"

LifeComponent::LifeComponent(unsigned int life)
	: AComponent("LifeComponent")
{
	this->_life = life;
}

LifeComponent::LifeComponent(const LifeComponent &ref)
: AComponent("LifeComponent")
{
	this->_life = ref._life;
}


LifeComponent::~LifeComponent()
{}

//----- ----- Operators ----- ----- //
LifeComponent	&LifeComponent::operator=(const LifeComponent &ref)
{
	this->_life = ref._life;
	return (*this);
}

//----- ----- Getters ----- ----- //
unsigned int	LifeComponent::getLife() const
{
	return (this->_life);
}

void LifeComponent::setLife(const unsigned int life)
{
	this->_life = life;
}

void		LifeComponent::serialize(IBuffer &buffer) const
{
	buffer << this->_life;
}

void		LifeComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_life;
}
