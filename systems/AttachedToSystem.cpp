#include "AttachedToSystem.hh"
#include "AttachedToComponent.hh"
#include "Pos2DComponent.hh"
#include "Entity.hh"
#include "EntityDeletedEvent.hh"

AttachedToSystem::AttachedToSystem() : ASystem("AttachedToSystem")
{}

AttachedToSystem::~AttachedToSystem()
{}

bool AttachedToSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("AttachedToComponent") && entity->hasComponent("Pos2DComponent"))
    return true;
  return false;
}

void AttachedToSystem::processEntity(Entity *entity, const float)
{
  AttachedToComponent *attachedto = entity->getComponent<AttachedToComponent>("AttachedToComponent");
  Pos2DComponent *pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");

  if (!attachedto || !pos)
    return ;
  Entity *follow_entity = this->_world->getEntity(attachedto->getEntityIDAttachedTo());
  if (!follow_entity)
    {
      this->_world->sendEvent(new EntityDeletedEvent(entity));
      return;
    }
  Pos2DComponent *follow_pos = follow_entity->getComponent<Pos2DComponent>("Pos2DComponent");

  pos->setX(follow_pos->getX() + attachedto->getOffset().first);
  pos->setY(follow_pos->getY() + attachedto->getOffset().second);
}
