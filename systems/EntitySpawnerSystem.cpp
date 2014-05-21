#include	"EntitySpawnerSystem.hh"
#include	"EntitySpawnerComponent.hh"
#include	"Pos2DComponent.hh"

//----- ----- Constructors ----- ----- //
EntitySpawnerSystem::EntitySpawnerSystem()
  : ASystem("EntitySpawnerSystem")
{}

//----- ----- Destructor ----- ----- //
EntitySpawnerSystem::~EntitySpawnerSystem()
{}

//----- ----- Getters ----- ----- //
//----- ----- Setters ----- ----- //
//----- ----- Methods ----- ----- //
bool		EntitySpawnerSystem::canProcess(Entity *e)
{
  if (e->hasComponent("EntitySpawnerComponent"))
    return (true);
  return (false);
}

void		EntitySpawnerSystem::processEntity(Entity *e, const float)
{
  EntitySpawnerComponent	*spawner;
  Entity			*entity;

  if (!(spawner = e->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent")))
    return ;
  entity = spawner->spawnEntity(this->_world->getSharedObject<EntityFactory>("entityFactory"),
				e->getComponent<Pos2DComponent>("Pos2DComponent"));
  if (!entity)
    return ;
  this->_world->addEntity(entity);
}
