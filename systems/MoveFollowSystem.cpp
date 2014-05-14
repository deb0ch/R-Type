#include "MoveFollowSystem.hh"
#include "MoveFollowComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveFollowSystem::MoveFollowSystem() : ASystem("MoveFollowSystem")
{}

MoveFollowSystem::~MoveFollowSystem()
{}

bool MoveFollowSystem::canProcess(Entity *entity)
{
	if (entity->hasComponent("MoveFollowComponent") &&
		entity->hasComponent("ActionComponent") &&
		entity->hasComponent("Pos2DComponent"))
		return (true);
	return (false);
}

void MoveFollowSystem::processEntity(Entity *entity, const float)
{
	ActionComponent		*action;
	MoveFollowComponent		*target;
	Entity			*entityToFollow;
	Pos2DComponent		*posEntity;

	action = entity->getComponent<ActionComponent>("ActionComponent");
	target = entity->getComponent<MoveFollowComponent>("MoveFollowComponent");
	posEntity = entity->getComponent<Pos2DComponent>("Pos2DComponent");

	if ((entityToFollow = this->_world->getEntity(target->getIdToFollow())) != NULL)
	{
		auto posToFollow = entityToFollow->getComponent<Pos2DComponent>("Pos2DComponent");
		if (!posToFollow)
			return;
		if (posEntity->getX() < posToFollow->getX())
			action->setAction("RIGHT", true);
		if (posEntity->getX() > posToFollow->getX())
			action->setAction("LEFT", true);
		if (posEntity->getY() < posToFollow->getY())
			action->setAction("DOWN", true);
		if (posEntity->getY() > posToFollow->getY())
			action->setAction("UP", true);
	}
}
