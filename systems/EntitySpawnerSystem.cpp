#include	"EntitySpawnerSystem.hh"
#include	"Pos2DComponent.hh"
#include	"TeamComponent.hh"

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

void		EntitySpawnerSystem::givePosition(Entity *e, EntitySpawnerComponent *spawner, Entity *res) const
{
  Pos2DComponent		*pos;
  Pos2DComponent		*res_pos;
  std::pair<float, float>	rand_coords;

  pos = e->getComponent<Pos2DComponent>("Pos2DComponent");

  res_pos = res->getComponent<Pos2DComponent>("Pos2DComponent");
  if (!res_pos)
    res->addComponent((res_pos = new Pos2DComponent(0, 0)));
  res_pos->setX(0);
  res_pos->setY(0);
  if (!spawner->isAbsolute() && pos)
    {
      res_pos->setX(pos->getX());
      res_pos->setY(pos->getY());
    }
  rand_coords = spawner->getCoordinates();
  res_pos->setX(res_pos->getX() + rand_coords.first);
  res_pos->setY(res_pos->getY() + rand_coords.second);
}

void		EntitySpawnerSystem::giveTeam(Entity *e, Entity *res) const
{
  TeamComponent		*team;
  TeamComponent		*res_team;

  if (!(team = e->getComponent<TeamComponent>("TeamComponent")))
    return ;
  res_team = res->getComponent<TeamComponent>("TeamComponent");
  if (!res_team)
    res->addComponent((res_team = new TeamComponent()));
  res_team->setTeam(team->getTeam());
}

void		EntitySpawnerSystem::giveComponents(EntitySpawnerComponent *spawner, Entity *res) const
{
  std::for_each(spawner->getComponents().begin(),
		spawner->getComponents().end(),
		[res] (IComponent* comp) -> void {
		  res->addComponent(comp->clone());
		});
}

void		EntitySpawnerSystem::processEntity(Entity *e, const float)
{
  EntitySpawnerComponent	*spawner;
  Entity			*res;

  if (!(spawner = e->getComponent<EntitySpawnerComponent>("EntitySpawnerComponent")))
    return ;
  if (!(res = spawner->spawnEntity(this->_world->getSharedObject<EntityFactory>("entityFactory"))))
    return ;

  this->givePosition(e, spawner, res);
  this->giveTeam(e, res);
  this->giveComponents(spawner, res);

  this->_world->addEntity(res);
}
