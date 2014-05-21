#include "MoveForwardSystem.hh"
#include "MoveForwardComponent.hh"
#include "ActionComponent.hh"
#include "Pos2DComponent.hh"

MoveForwardSystem::MoveForwardSystem() : ASystem("MoveForwardSystem")
{}

MoveForwardSystem::~MoveForwardSystem()
{}

bool MoveForwardSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("MoveForwardComponent") &&
      entity->hasComponent("ActionComponent") &&
      entity->hasComponent("Pos2DComponent"))
    return (true);
  return (false);
}

void MoveForwardSystem::processEntity(Entity *entity, const float)
{
  ActionComponent		*action;
  MoveForwardComponent		*moveEntity;
  Pos2DComponent		*posEntity;

  action = entity->getComponent<ActionComponent>("ActionComponent");
  moveEntity = entity->getComponent<MoveForwardComponent>("MoveForwardComponent");
  posEntity = entity->getComponent<Pos2DComponent>("Pos2DComponent");

  std::vector<std::string> movements = moveEntity->getDirection();
  for (unsigned int i = 0; i < movements.size(); i++)
    {
      //std::cout << movements[i] << std::endl;
      //std::cout << movements.size() << std::endl;
      action->setAction(movements[i], true);
    }
}
