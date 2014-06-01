#include "AttachPowerUpComponent.hh"
#include "AttachComponent.hh"

AttachPowerUpComponent::AttachPowerUpComponent(const std::string &entity_name)
  : APowerUpComponent("AttachPowerUpComponent")
{
  this->_entity_name = entity_name;
}

AttachPowerUpComponent::~AttachPowerUpComponent()
{}

void	AttachPowerUpComponent::upgrade(World *, Entity *entity)
{
  if (entity && !entity->hasComponent("AttachComponent"))
    entity->addComponent(new AttachComponent(this->_entity_name));
}

void	AttachPowerUpComponent::deserializeFromFileSpecial(const std::string &lastline,
							   std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("entity=.+")))
    this->_entity_name = lastline.substr(7);
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	AttachPowerUpComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "entity=" << this->_entity_name << std::endl;
}

ASerializableComponent	*AttachPowerUpComponent::cloneSerializable() const
{
  return (new AttachPowerUpComponent(*this));
}
