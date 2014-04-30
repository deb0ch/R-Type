#include	"ASystem.hh"
#include	<algorithm>

//----- ----- Constructors ----- ----- //
ASystem::ASystem(unsigned int priority)
{
  this->_priority = priority;
}

//----- ----- Destructor ----- ----- //
ASystem::~ASystem()
{}

//----- ----- Getters ----- ----- //
unsigned int	ASystem::getPriority() const
{
  return this->_priority;
}

//----- ----- Methods ----- ----- //
void		ASystem::setWorld(World *world)
{
  this->_world = world;
}

//----- ----- Methods ----- ----- //
void		ASystem::process(std::vector<Entity *> &entities)
{
  std::for_each(entities.begin(), entities.end(), [this] (Entity *entity) -> void {
      if (this->canProcess(entity))
	this->processEntity(entity);
    });
}
