#include "LifeComponent.hh"

LifeComponent::LifeComponent(unsigned int life, unsigned int invulnerability)
	: AComponent("LifeComponent")
{
	this->_life = life;
	this->_invulnerability = 0;
	this->_invulenerabilityMaxTime = invulnerability;
}

LifeComponent::~LifeComponent()
{}

//----- ----- Operators ----- ----- //
//----- ----- Getters ----- ----- //
unsigned int	LifeComponent::getLife() const
{
	return (this->_life);
}

void LifeComponent::decreaseLife(const unsigned int damages)
{
	if (this->_invulnerability)
		return;
	if (damages >= this->_life)
		this->_life = 0;
	else
		this->_life -= damages;
	this->_invulnerability = this->_invulenerabilityMaxTime;
}

void LifeComponent::gainLife(const unsigned int heal)
{
	this->_life += heal;
}

void		LifeComponent::serialize(IBuffer &buffer) const
{
	buffer << this->_life;
}

void		LifeComponent::unserialize(IBuffer &buffer)
{
	buffer >> this->_life;
}

bool LifeComponent::isInvulnerable() const
{
	return (this->_invulnerability > 0);
}

void LifeComponent::decreaseInvulnerability()
{
	if (this->_invulnerability > 0)
		--(this->_invulnerability);
}
