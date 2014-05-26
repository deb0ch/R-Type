#include <iostream>

#include "TagComponent.hh"
#include "SFMLSpriteComponent.hh"
#include "Pos2DComponent.hh"
#include "BackgroundSystem.hh"

BackgroundSystem::BackgroundSystem() : ASystem("BackgroundSystem")
{
}

BackgroundSystem::~BackgroundSystem()
{
}

bool	BackgroundSystem::canProcess(Entity *entity)
{
  TagComponent *tagComponent = entity->getComponent<TagComponent>("TagComponent");

  if (tagComponent &&
      entity->hasComponent("SFMLSpriteComponent") &&
      entity->hasComponent("Pos2DComponent") &&
      tagComponent->hasTag("BackgroundSystem"))
    return (true);
  return (false);
}

void	BackgroundSystem::processEntity(Entity *entity, const float)
{
  Pos2DComponent	*entity_pos;

  entity_pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  if (entity_pos->getX() <= -1095)
    entity_pos->setX(1095);
}
