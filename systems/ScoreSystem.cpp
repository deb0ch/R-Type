#include "ScoreSystem.hh"
#include "EntityDeletedEvent.hh"
#include "TagComponent.hh"
#include "IPlayerRespawner.hh"

ScoreSystem::ScoreSystem() : ASystem("ScoreSystem")
{
  this->_score = 0;
}

ScoreSystem::~ScoreSystem()
{}

void	ScoreSystem::init()
{
  this->_world->addEventHandler("EntityDeletedEvent", this, &ScoreSystem::entityDeathEvent);
}

bool	ScoreSystem::canProcess(Entity *) const
{
  return (false);
}

void	ScoreSystem::processEntity(Entity *, const float)
{}

void	ScoreSystem::entityDeathEvent(IEvent *event)
{
  EntityDeletedEvent	*entityDeletedEvent = dynamic_cast<EntityDeletedEvent *>(event);

  if (!entityDeletedEvent)
    return ;

  TagComponent *tag = entityDeletedEvent->getEntity()->getComponent<TagComponent>("TagComponent");
  if (!tag || !tag->hasTag("MONSTER") || entityDeletedEvent->isForced())
    return ;
  this->_score += (tag->hasTag("BOSS")) ? 500 : 10;
}

unsigned int	ScoreSystem::getScore() const
{
  return this->_score;
}
