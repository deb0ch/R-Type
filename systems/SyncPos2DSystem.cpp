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
  if (entity->hasComponent("SyncPos2DComponent")
      && entity->hasComponent("Pos2DComponent")
      && entity->hasComponent("NetworkReceiveUpdateComponent"))
    return true;
  return false;
}

void		SyncPos2DSystem::processEntity(Entity *entity, const float)
{
  SyncPos2DComponent	*sync_comp = entity->getComponent<SyncPos2DComponent>("SyncPos2DComponent");
  Pos2DComponent	*pos_comp = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  float			delta_x;
  float			delta_y;

  if (sync_comp->getRatio() != 0)
    {
      delta_x = sync_comp->getSyncPos().getX() / sync_comp->getRatio();
      delta_y = sync_comp->getSyncPos().getY() / sync_comp->getRatio();
    }
  else
    {
      delta_x = 0;
      delta_y = 0;
    }
  pos_comp->setX(pos_comp->getX() + delta_x);
  pos_comp->setY(pos_comp->getY() + delta_y);
  sync_comp->getSyncPos().setX(sync_comp->getSyncPos().getX() - delta_x);
  sync_comp->getSyncPos().setY(sync_comp->getSyncPos().getY() - delta_y);
}
