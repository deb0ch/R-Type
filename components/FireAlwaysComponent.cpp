#include "FireAlwaysComponent.hh"

//----- ----- Constructors ----- ----- //
FireAlwaysComponent::FireAlwaysComponent()
  : ACopyableComponent("FireAlwaysComponent")
{}

//----- ----- Destructor ----- ----- //
FireAlwaysComponent::~FireAlwaysComponent()
{}

//----- ----- Methods ----- ----- //

void	FireAlwaysComponent::serialize(IBuffer &) const
{}

void	FireAlwaysComponent::unserialize(IBuffer &)
{}

void	FireAlwaysComponent::serializeFromFile(std::ofstream &, unsigned char) const
{}
