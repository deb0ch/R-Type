#include	<algorithm>
#include	"ASystem.hh"
#include	"IEvent.hh"

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
void		ASystem::process(std::vector<Entity *> &entities, const float delta)
{
  this->beforeProcess(delta);
  this->sortEntities(entities);
  std::for_each(entities.begin(), entities.end(), [this, delta] (Entity *entity) -> void {
      try
	{
	  if (this->canProcess(entity))
	    this->processEntity(entity, delta);
	}
      catch (const std::exception &e)
	{
	  std::cerr << "Error in system " << this->getType() << ":" << std::endl << e.what() << std::endl;
	}
    });
  this->afterProcess(delta);
}

void		ASystem::sortEntities(std::vector<Entity *>&)
{}

void		ASystem::beforeProcess(const float)
{}

void		ASystem::afterProcess(const float)
{}

void		ASystem::init()
{}

void		ASystem::start()
{}

void		ASystem::pause()
{}

void		ASystem::resume()
{}

void		ASystem::stop()
{}
