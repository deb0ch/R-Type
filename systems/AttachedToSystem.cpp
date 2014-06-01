#include "AttachedToSystem.hh"
#include "AttachedToComponent.hh"
#include "Pos2DComponent.hh"
#include "Entity.hh"
#include "EntityDeletedEvent.hh"
#include "ActionComponent.hh"
#include "EntitySpawnerComponent.hh"

AttachedToSystem::AttachedToSystem() : ASystem("AttachedToSystem")
{}

AttachedToSystem::~AttachedToSystem()
{}

bool AttachedToSystem::canProcess(Entity *entity) const
{
  if (entity->hasComponent("AttachedToComponent") && entity->hasComponent("Pos2DComponent"))
    return true;
  return false;
}

void AttachedToSystem::processEntity(Entity *entity, const float)
{
  AttachedToComponent *attachedto = entity->getComponent<AttachedToComponent>("AttachedToComponent");
  Pos2DComponent *pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  ActionComponent *follow_action_component;
  EntitySpawnerComponent *entity_spawner;
  EntitySpawnerComponent *follow_entity_spawner;
  Pos2DComponent *follow_pos;

  if (!attachedto || !pos)
    return ;
  Entity *follow_entity = this->_world->getEntity(attachedto->getEntityIDAttachedTo());
  if (!follow_entity)
    {
      this->_world->sendEvent(new EntityDeletedEvent(entity));
      return;
    }
  follow_pos = follow_entity->getComponent<Pos2DComponent>("Pos2DComponent");
  pos->setX(follow_pos->getX() + attachedto->getOffset().first);
  pos->setY(follow_pos->getY() + attachedto->getOffset().second);

  follow_action_component = follow_entity->getComponent<ActionComponent>("ActionComponent");
  entity_spawner = entity->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent");
  follow_entity_spawner = follow_entity->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent");
  if (follow_action_component && follow_action_component->isActive("FIRE") &&
      entity_spawner && follow_entity_spawner)
    {
      std::string tmp = follow_entity_spawner->getLastSpawned();
      float delay = follow_entity_spawner->getDelay();
      entity_spawner->clearEntities();
      entity_spawner->addEntity(std::make_pair(tmp, 1));
      entity_spawner->setDelay(delay);
      entity_spawner->setActive(true);
    }
  else if (entity_spawner)
    entity_spawner->setActive(false);
}
