#include	"SFMLInputComponent.hh"

SFMLInputComponent::SFMLInputComponent()
  : ACopyableComponent("SFMLInputComponent")
{}

SFMLInputComponent::~SFMLInputComponent()
{}

void SFMLInputComponent::serialize(IBuffer &) const
{}

void SFMLInputComponent::unserialize(IBuffer &)
{}

void	SFMLInputComponent::serializeFromFile(std::ofstream &, unsigned char) const
{}
