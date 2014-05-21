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
  Pos2DComponent		*pos;
  Entity			*entity;
  Pos2DComponent		*entity_pos;
  std::pair<float, float>	rand_coords;

  if (!(spawner = e->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent")))
    return ;
  entity = spawner->spawnEntity(this->_world->getSharedObject<EntityFactory>("entityFactory"));
  if (!entity)
    return ;
  pos = e->getComponent<Pos2DComponent>("Pos2DComponent");

  entity_pos = entity->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!entity_pos)
    {
      entity_pos = new Pos2DComponent(0, 0);
      entity->addComponent(entity_pos);
    }
  entity_pos->setX(0);
  entity_pos->setY(0);
  if (!spawner->isAbsolute() && pos)
    {
      entity_pos->setX(pos->getX());
      entity_pos->setY(pos->getY());
    }
  rand_coords = spawner->getCoordinates();
  entity_pos->setX(entity_pos->getX() + rand_coords.first);
  entity_pos->setY(entity_pos->getY() + rand_coords.second);

  this->_world->addEntity(entity);
}
