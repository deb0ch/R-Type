#include "AttachedToComponent.hh"
#include "NetworkReceiveUpdateComponent.hh"

AttachedToComponent::AttachedToComponent(unsigned int id, const std::pair<int, int> &offset)
  : ACopyableComponent("AttachedToComponent")
{
  this->_entity_id = id;
  this->_offset = offset;
}

AttachedToComponent::~AttachedToComponent()
{}

void AttachedToComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_entity_id;
  buffer << this->_offset.first;
  buffer << this->_offset.second;
}

void AttachedToComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_entity_id;
  buffer >> this->_offset.first;
  buffer >> this->_offset.second;
}

void		AttachedToComponent::networkUnserializeCallback(IBuffer &, World *world, Entity *)
{
  auto it = std::find_if(world->getEntities().begin(), world->getEntities().end(),
			 [this] (const Entity *entity)
			 {
			   NetworkReceiveUpdateComponent *network_comp;

			   network_comp =
			   entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
			   if (network_comp)
			     {
			       if (network_comp->getRemoteID() == this->_entity_id)
				 return true;
			     }
			   return false;
			 });
  if (it != world->getEntities().end())
    {
      this->_entity_id = (*it)->_id;
    }
}

unsigned int	AttachedToComponent::getEntityIDAttachedTo() const
{
  return this->_entity_id;
}

const std::pair<int, int> &AttachedToComponent::getOffset() const
{
  return this->_offset;
}

void AttachedToComponent::deserializeFromFileSpecial(const std::string & lastline,
						     std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("entity_id=.+")))
    this->_entity_id = std::stoul(lastline.substr(10));
  else if (std::regex_match(lastline, std::regex("offset_x=.+")))
    this->_offset.first = std::stoul(lastline.substr(9));
  else if (std::regex_match(lastline, std::regex("offset_y=.+")))
    this->_offset.second = std::stoul(lastline.substr(9));
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void AttachedToComponent::serializeFromFile(std::ofstream & output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "entity_id=" << this->_entity_id << std::endl;
  output << std::string(indent, '\t') << "offset_x=" << this->_offset.first << std::endl;
  output << std::string(indent, '\t') << "offset_y=" << this->_offset.second << std::endl;
}
