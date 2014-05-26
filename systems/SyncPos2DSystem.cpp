#include "SyncPos2DSystem.hh"
#include "SyncPos2DComponent.hh"
#include "Pos2DComponent.hh"
#include "NetworkReceiveUpdateComponent.hh"

SyncPos2DSystem::SyncPos2DSystem() : ASystem("SyncPos2DSystem")
{}

SyncPos2DSystem::~SyncPos2DSystem()
{}

bool		SyncPos2DSystem::canProcess(Entity *entity)
{
  if (entity->hasComponent("SyncPos2DComponent") && entity->hasComponent("Pos2DComponent") &&
      entity->hasComponent("NetworkReceiveUpdateComponent"))
    return true;
  return false;
}

// Needs to be redone completly
void		SyncPos2DSystem::processEntity(Entity *entity, const float)
{
  SyncPos2DComponent	*sync_comp = entity->getComponent<SyncPos2DComponent>("SyncPos2DComponent");
  Pos2DComponent	*pos_comp = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  NetworkReceiveUpdateComponent *network_comp =
    entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
  float			delta_x;
  float			delta_y;
  float			ratio;

  if (network_comp->getPreviousUpdateTime() <= 1)
    {
      pos_comp->setX(sync_comp->getSyncPos().getX());
      pos_comp->setY(sync_comp->getSyncPos().getY());
      return ;
    }
  ratio = network_comp->getLastUpdate() / network_comp->getPreviousUpdateTime();
  delta_x = (sync_comp->getSyncPos().getX() - pos_comp->getX()) * ratio;
  delta_y = (sync_comp->getSyncPos().getY() - pos_comp->getY()) * ratio;
  pos_comp->setX(pos_comp->getX() + delta_x);
  pos_comp->setY(pos_comp->getY() + delta_y);
}
