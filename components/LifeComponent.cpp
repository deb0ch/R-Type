#include "LifeComponent.hh"

LifeComponent::LifeComponent(unsigned int life, float invulnerability)
	: ACopyableComponent("LifeComponent")
{
	this->_life = life;
	this->_invulnerability = 0;
	this->_invulnerabilityMaxTime = invulnerability;
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
	if (this->isInvulnerable())
		return;
	if (damages >= this->_life)
		this->_life = 0;
	else
		this->_life -= damages;
	this->_invulnerability = this->_invulnerabilityMaxTime;
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

void LifeComponent::setInvulnerabilityTime(float time)
{
  this->_invulnerability = time;
}

void LifeComponent::decreaseInvulnerability(float delta)
{
	if (this->_invulnerability > 0)
		this->_invulnerability -= delta;
}

void	LifeComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("life.+")))
    this->_life = std::stoul(lastline.substr(5));
  else if (std::regex_match(lastline, std::regex("invulnerability=.+")))
    this->_invulnerabilityMaxTime = std::stoul(lastline.substr(16));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	LifeComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "life=" << this->_life << std::endl;
  output << std::string(indent, '\t') << "invulnerability=" << this->_invulnerabilityMaxTime << std::endl;
}
