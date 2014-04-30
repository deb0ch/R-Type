#include "ASystem.hh"
#include <algorithm>

ASystem::ASystem()
{
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
