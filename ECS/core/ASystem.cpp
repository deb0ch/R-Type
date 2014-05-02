#include	"ASystem.hh"
#include	<algorithm>

//----- ----- Constructors ----- ----- //
ASystem::ASystem(const std::string &type, unsigned int priority)
{
  this->_type = type;
  this->_priority = priority;
}

//----- ----- Destructor ----- ----- //
ASystem::~ASystem()
{}

//----- ----- Getters ----- ----- //
const std::string	&ASystem::getType() const
{
  return (this->_type);
}

unsigned int	ASystem::getPriority() const
{
  return this->_priority;
}

//----- ----- Setters ----- ----- //
void		ASystem::setWorld(World *world)
{
  this->_world = world;
}

//----- ----- Methods ----- ----- //
void		ASystem::process(std::vector<Entity *> &entities)
{
  this->sortEntities(entities);
  std::for_each(entities.begin(), entities.end(), [this] (Entity *entity) -> void {
      if (this->canProcess(entity))
	this->processEntity(entity);
    });
}