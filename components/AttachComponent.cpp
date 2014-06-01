#include "AttachComponent.hh"

AttachComponent::AttachComponent(const std::string & entity_name) : ACopyableComponent("AttachComponent")
{
  this->_entity_name = entity_name;
  this->_initialized = false;
}

AttachComponent::~AttachComponent()
{}

// Will never be serialized
void AttachComponent::serialize(IBuffer &) const
{}

void AttachComponent::unserialize(IBuffer &)
{}

bool AttachComponent::isInitiliazed() const
{
  return this->_initialized;
}

void AttachComponent::setInitiliazed()
{
  this->_initialized = true;
}

const std::string &AttachComponent::getEntityName() const
{
  return this->_entity_name;
}

void AttachComponent::deserializeFromFileSpecial(const std::string & lastline,
						 std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("entity=.+")))
    this->_entity_name = lastline.substr(7);
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void AttachComponent::serializeFromFile(std :: ofstream & output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "entity=" << this->_entity_name << std::endl;
}
