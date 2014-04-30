#include "ASystem.hh"
#include <algorithm>

ASystem::ASystem(unsigned int priority)
{
  this->_priority = priority;
}

ASystem::~ASystem()
{
}

void ASystem::process(std::vector<Entity *> &entities)
{
  std::for_each(entities.begin(), entities.end(), [this] (Entity *entity) -> void {
      if (this->canProcess(entity))
	this->processEntity(entity);
    });
}

unsigned int	ASystem::getPriority() const
{
  return this->_priority;
}
