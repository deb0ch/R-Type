#include	<iostream>

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"
#include	"SFMLInputSystem.hh"
#include	"ActionMovementSystem.hh"
#include	"EntityDeleterSystem.hh"
#include	"OutOfBoundsSystem.hh"
#include	"NetworkSendUpdateSystem.hh"
#include	"NetworkReceiveUpdateSystem.hh"
#include	"SFMLEventSystem.hh"
#include	"MoveFollowSystem.hh"
#include	"MoveForwardSystem.hh"
#include	"MoveSequenceSystem.hh"
#include	"ResetActionSystem.hh"
#include	"LifeSystem.hh"
#include	"BackgroundSystem.hh"
#include	"EntitySpawnerSystem.hh"
#include	"ActionFireSystem.hh"
#include	"FireAlwaysSystem.hh"
#include	"MovementLimitFrame2DSystem.hh"
#include	"AutoDestructSystem.hh"
#include	"NetworkSendActionSystem.hh"
#include	"NetworkReceiveActionSystem.hh"
#include	"SpawnPlayerSystem.hh"
#include	"NetworkSendDieEntitySystem.hh"
#include	"DisconnectPlayerSystem.hh"

#include	"ComponentFactory.hpp"
#include	"ImageLoader.hh"
#include	"EntityFactory.hpp"
#include	"Entity.hh"
#include	"ServerRelay.hh"
#include	"RunWorldServer.hh"

RunWorldServer::RunWorldServer(ServerRelay *server, const std::string &nameRoom) {
  this->_server = server;
  this->_nameRoom = nameRoom;
  this->_world = new World();
  this->addSystems();
  this->addSharedObjetcs();
  this->addEntities();
}

void RunWorldServer::run(Any)
{
  this->run();
}

void RunWorldServer::run() {
  this->_world->start();
  while (42) {
    this->_timer.startFrame();
    if (this->_timer.canTick())
      this->_world->process(this->_timer.getDeltaTime() / 1000000.f);
    this->_timer.endFrame();
  }
}

RunWorldServer::~RunWorldServer() {
  this->_world->stop();
  delete this->_world;
}

World *RunWorldServer::getWorld() {
  return this->_world;
}


/**************** PRIVATE ****************/

void RunWorldServer::addSystems()
{
  this->_world->addSystem(new AutoDestructSystem());
  this->_world->addSystem(new EntitySpawnerSystem());
  this->_world->addSystem(new SFMLEventSystem());
  this->_world->addSystem(new SFMLRenderSystem());
  this->_world->addSystem(new OutOfBoundsSystem());
  this->_world->addSystem(new MoveFollowSystem());
  this->_world->addSystem(new MoveForwardSystem());
  this->_world->addSystem(new MoveSequenceSystem());
  this->_world->addSystem(new FireAlwaysSystem());
  this->_world->addSystem(new ActionMovementSystem());
  this->_world->addSystem(new ActionFireSystem());
  this->_world->addSystem(new Friction2DSystem());
  this->_world->addSystem(new MoveSystem());
  this->_world->addSystem(new LifeSystem());
  this->_world->addSystem(new ResetActionSystem());
  this->_world->addSystem(new MovementLimitFrame2DSystem());
  this->_world->addSystem(new SpawnPlayerSystem());
  this->_world->addSystem(new DisconnectPlayerSystem());
  this->_world->addSystem(new BackgroundSystem());

  CollisionSystem *collision = new CollisionSystem();
  this->_world->addSystem(collision);
  this->_world->addEventHandler("CollisionEvent", collision, &LifeSystem::collision_event);

  NetworkSendDieEntitySystem *networkSendDieEntitySystem = new NetworkSendDieEntitySystem();
  this->_world->addSystem(networkSendDieEntitySystem);
  this->_world->addEventHandler("EntityDeletedEvent", networkSendDieEntitySystem,
			&NetworkSendDieEntitySystem::addEntityToDelete);

  EntityDeleterSystem *entityDeleterSystem = new EntityDeleterSystem();
  this->_world->addSystem(entityDeleterSystem);
  this->_world->addEventHandler("EntityDeletedEvent", entityDeleterSystem,
			&EntityDeleterSystem::addEntityToDelete);
  this->_world->addEventHandler("EntityDeletedEvent", entityDeleterSystem, &LifeSystem::delete_entity);

  std::vector<std::string> arg =
    {
      "Pos2DComponent",
      "SFMLSpriteComponent",
      "Speed2DComponent",
      "Friction2DComponent",
      "ActionComponent",
      "MovementSpeedComponent",
      "NetworkSendActionComponent",
      "SFMLInputComponent",
      "MovementSpeedComponent",
      "NetworkPlayerComponent",
      "MoveForwardComponent",
      "MoveSequenceComponent",
      "Box2DComponent"
    };

  this->_world->addSystem(new NetworkSendUpdateSystem(arg));

  std::vector<std::string> serializable_action =
    {
      "UP",
      "RIGHT",
      "DOWN",
      "LEFT",
      "FIRE"
    };

  this->_world->addSystem(new NetworkReceiveActionSystem(serializable_action));
}

void RunWorldServer::addSharedObjetcs()
{
  ComponentFactory *compos = new ComponentFactory();
  EntityFactory *entityFactory = new EntityFactory();

  this->_world->setSharedObject("NetworkRelay", static_cast<INetworkRelay *>(this->_server));
  this->_world->setSharedObject("RoomName", &this->_nameRoom);
  compos->init();
  entityFactory->init();
  this->_world->setSharedObject("imageLoader", new ImageLoader());
  this->_world->setSharedObject("componentFactory", compos);
  this->_world->setSharedObject("entityFactory", entityFactory);
}

void	RunWorldServer::addEntities()
{
  EntityFactory *entityFactory = this->_world->getSharedObject<EntityFactory>("entityFactory");

  if (entityFactory == NULL)
    return;
  this->_world->addEntity(entityFactory->create("BACKGROUND_1"));
  this->_world->addEntity(entityFactory->create("BACKGROUND_2"));
  this->_world->addEntity(entityFactory->create("BOSS_1"));
  this->_world->addEntity(entityFactory->create("MONSTER_SPAWNER"));
}
