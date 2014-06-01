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
  ActionComponent *follow_action_component;
  ActionComponent *action_comp;
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
  action_comp = entity->getComponent<ActionComponent>("ActionComponent");
  if (follow_action_component && follow_action_component->isActive("FIRE"))
    {
      if (action_comp)
	{
	  std::cout << "SET FIRE" << std::endl;
	  action_comp->setAction("FIRE", true);
	}
    }
  else if (action_comp)
    action_comp->setAction("FIRE", false);
}
