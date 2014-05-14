#include "MoveSequenceSystem.hh"
#include "MoveSequenceComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveSequenceSystem::MoveSequenceSystem() : ASystem("MoveSequenceSystem")
{}

MoveSequenceSystem::~MoveSequenceSystem()
{}

bool MoveSequenceSystem::canProcess(Entity *entity)
{
	if (entity->hasComponent("MoveSequenceComponent") &&
		entity->hasComponent("ActionComponent") &&
		entity->hasComponent("Pos2DComponent"))
		return (true);
	return (false);
}

void MoveSequenceSystem::processEntity(Entity *entity, const float)
{
	ActionComponent		*action;
	MoveSequenceComponent *moveEntity;
	Pos2DComponent		*posEntity;

	action = entity->getComponent<ActionComponent>("ActionComponent");
	moveEntity = entity->getComponent<MoveSequenceComponent>("MoveSequenceComponent");
	posEntity = entity->getComponent<Pos2DComponent>("Pos2DComponent");

	if (moveEntity != NULL)
	{
		action->setAction(moveEntity->getAction(), true);
		moveEntity->incrementTick();
	}
}