
#include	"MoveFollowComponent.hh"
#include	"Pos2DComponent.hh"
#include	"NetworkReceiveUpdateComponent.hh"

//----- ----- Constructors ----- ----- //
MoveFollowComponent::MoveFollowComponent(const std::string & tagToFollow)
  : ACopyableComponent("MoveFollowComponent"), _idToFollow(0)
{
  this->_tagToFollow = tagToFollow;
}

//----- ----- Destructor ----- ----- //
MoveFollowComponent::~MoveFollowComponent()
{}

unsigned int	MoveFollowComponent::getIdToFollow() const
{
  return this->_idToFollow;
}

void		MoveFollowComponent::setIdToFollow(unsigned int idToFollow)
{
  this->_idToFollow = idToFollow;
}

const std::string &	MoveFollowComponent::getTagToFollow() const
{
  return this->_tagToFollow;
}

void		MoveFollowComponent::serialize(IBuffer &buffer) const
{
  buffer << this->_idToFollow;
  buffer << this->_tagToFollow;
}

void		MoveFollowComponent::unserialize(IBuffer &buffer)
{
  buffer >> this->_idToFollow;
  buffer >> this->_tagToFollow;
}

void		MoveFollowComponent::networkUnserializeCallback(IBuffer &, World *world, Entity *)
{
  auto it = std::find_if(world->getEntities().begin(), world->getEntities().end(),
			 [this] (const Entity *entity)
			 {
			   NetworkReceiveUpdateComponent *network_comp;

			   network_comp =
			   entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
			   if (network_comp)
			     {
			       if (network_comp->getRemoteID() == this->_idToFollow)
				 return true;
			     }
			   return false;
			 });
  if (it != world->getEntities().end())
    {
      this->_idToFollow = (*it)->_id;
    }
}


//----- ----- Setters ----- ----- //

void		MoveFollowComponent::setTagToFollow(const std::string & tagToFollow)
{
  this->_tagToFollow = tagToFollow;
}

void	MoveFollowComponent::deserializeFromFileSpecial(const std::string &lastline, std::ifstream &input, unsigned int &lineno)
{
  (void)input;

  if (std::regex_match(lastline, std::regex("tagToFollow=.+")))
    this->_tagToFollow = lastline.substr(12);
  else
    throw EntityFileException("Bad argument : \"" + lastline + "\"", lineno);
}

void	MoveFollowComponent::serializeFromFile(std::ofstream &output, unsigned char indent) const
{
  output << std::string(indent, '\t') << "tagToFollow=" << this->_tagToFollow << std::endl;
}
