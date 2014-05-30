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

void	FireAlwaysComponent::deserializeFromFileSpecial(const std::string &, std::ifstream &, unsigned int &)
{}

void	FireAlwaysComponent::serializeFromFile(std::ofstream &, unsigned char) const
{}
