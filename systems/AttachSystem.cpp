#include "AttachSystem.hh"
#include "AttachComponent.hh"
#include "AttachedToComponent.hh"
#include "EntityFactory.hpp"

AttachSystem::AttachSystem() : ASystem("AttachSystem")
{}

AttachSystem::~AttachSystem()
{}

bool AttachSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("AttachComponent"))
    return true;
  return false;
}

void AttachSystem::processEntity(Entity *entity, const float)
{
  AttachComponent	*attach_component;
  EntityFactory		*entity_factory;
  Entity		*new_entity;

  attach_component = entity->getComponent<AttachComponent>("AttachComponent");
  entity_factory = this->_world->getSharedObject<EntityFactory>("entityFactory");
  if (!attach_component)
    return ;
  if (!attach_component->isInitiliazed())
    {
      attach_component->setInitiliazed();
      if ((new_entity = entity_factory->create(attach_component->getEntityName())))
	{
	  new_entity->addComponent(new AttachedToComponent(entity->_id,
							   std::make_pair(25, 0)));
	  this->_world->addEntity(new_entity);
	}
    }
}
