#include	<iostream>

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"
#include	"SFMLInputSystem.hh"
#include	"PlayerMovementSystem.hh"
#include	"NetworkSendUpdateSystem.hh"
#include	"NetworkReceiveUpdateSystem.hh"
#include	"MoveSystem.hh"

#include	"Pos2DComponent.hh"
#include	"Speed2DComponent.hh"
#include	"Friction2DComponent.hh"
#include	"Box2DComponent.hh"
#include	"SFMLSpriteComponent.hh"
#include	"SFMLInputComponent.hh"
#include	"PlayerMovementComponent.hh"
#include	"MovementSpeedComponent.hh"
#include	"NetworkSendUpdateComponent.hh"
#include	"NetworkReceiveUpdateComponent.hh"

#include	"ImageLoader.hh"

#ifdef _WIN32
#define PATH "sprites\\"
#elif __linux__
#define PATH "sprites/"
#endif

int		main()
{
  World		world;

  world.addSystem(new MoveSystem());
  world.addSystem(new Friction2DSystem());
  world.addSystem(new SFMLRenderSystem());
  world.addSystem(new PlayerMovementSystem());
  world.addSystem(new SFMLInputSystem());

  world.setSharedObject("imageLoader", new ImageLoader());

  world.addEntity(world.createEntity()
		  ->addComponent(new Pos2DComponent(100.0f, 100.0f))
		  ->addComponent(new Box2DComponent(50.0f, 50.0f))
		  ->addComponent(new Speed2DComponent(5.f, 5.f))
		  ->addComponent(new Friction2DComponent(0.3f))
		  ->addComponent(new SFMLSpriteComponent(PATH + std::string("ship.png")))
		  ->addComponent(new SFMLInputComponent())
		  ->addComponent(new PlayerMovementComponent())
		  ->addComponent(new NetworkSendUpdateComponent())
		  ->addComponent(new MovementSpeedComponent(5)));

  world.addEntity(world.createEntity()
		  ->addComponent(new Pos2DComponent(200.0f, 200.0f))
		  ->addComponent(new Box2DComponent(50.0f, 50.0f))
		  ->addComponent(new Speed2DComponent(5.f, 5.f))
		  ->addComponent(new Friction2DComponent(0.3f))
		  ->addComponent(new SFMLSpriteComponent(PATH + std::string("ship.png")))
		  ->addComponent(new SFMLInputComponent())
		  ->addComponent(new PlayerMovementComponent())
		  ->addComponent(new NetworkSendUpdateComponent())
		  ->addComponent(new MovementSpeedComponent(2)));

  Entity *update_entity;

  update_entity = world.createEntity();
  update_entity->addComponent(new Pos2DComponent(100.0f, 0.f))
    ->addComponent(new Speed2DComponent(2.f, 2.f))
    ->addComponent(new NetworkSendUpdateComponent())
    ->addComponent(new NetworkReceiveUpdateComponent(update_entity->_id))
    ->addComponent(new SFMLSpriteComponent(PATH + std::string("ship2.png")));
  world.addEntity(update_entity);

  CollisionSystem *collision;

  collision = new CollisionSystem();
  world.addSystem(collision);
  world.addEventHandler("CollisionEvent", collision, &CollisionSystem::collision_event);

  NetworkSendUpdateSystem *network;
  std::vector<std::string> arg = {"Pos2DComponent", "SFMLSpriteComponent", "Speed2DComponent", "Friction2DComponent"};

  network = new NetworkSendUpdateSystem(arg);
  world.addSystem(network);
  world.addSystem(new NetworkReceiveUpdateSystem());

  std::string test("Les pigouins ça glisse!");
  world.setSharedObject<std::string>("Test", &test);
  std::cout << *world.getSharedObject<std::string>("Test") << std::endl;
  std::cout << world.getSharedObject<ASystem>("NO-K") << std::endl;

  world.registerComponent(new Pos2DComponent());
  world.registerComponent(new SFMLSpriteComponent());
  world.registerComponent(new Speed2DComponent());
  world.registerComponent(new Friction2DComponent());
  std::cout << world.createComponent("Pos2DComponent")->getType() << std::endl;

  world.start();
  for (;;)
    {
      world.process(0.16f);
      Pos2DComponent *tmp;
      NetworkReceiveUpdateComponent *tmp2;

      tmp = update_entity->getComponent<Pos2DComponent>("Pos2DComponent");
      tmp2 = update_entity->getComponent<NetworkReceiveUpdateComponent>("NetworkReceiveUpdateComponent");
      std::cout << "Remote id: " << tmp2->getRemoteID() << " id: " << update_entity->_id << std::endl;
      std::cout << tmp->getX() << " - " << tmp->getY() << std::endl;
      std::cout << std::endl;
    }
  world.stop();

  return (0);
}


  // world.addEntity(world.createEntity()
  // 		  ->addComponent(new Pos2DComponent(100.0f, 600.0f))
  // 		  ->addComponent(new Box2DComponent(10.0f, 10.0f))
  // 		  ->addComponent(new Speed2DComponent(5.f, 2.f))
  // 		  ->addComponent(new SFMLSpriteComponent("sprites/ship.png"))
  // 		  ->addComponent(new NetworkSendUpdateComponent()));

  // world.addEntity(world.createEntity()
  // 		  ->addComponent(new Pos2DComponent(800.0f, 000.0f))
  // 		  ->addComponent(new Box2DComponent(10.0f, 10.0f))
  // 		  ->addComponent(new Speed2DComponent(-4.f, 5.f))
  // 		  ->addComponent(new SFMLSpriteComponent("sprites/ship.png"))
  // 		  ->addComponent(new NetworkSendUpdateComponent()));

  // world.addEntity(world.createEntity()
  // 		  ->addComponent(new Pos2DComponent(300.0f, 000.0f))
  // 		  ->addComponent(new Box2DComponent(10.0f, 10.0f))
  // 		  ->addComponent(new Speed2DComponent(20.f, 5.f))
  // 		  ->addComponent(new SFMLSpriteComponent("sprites/ship.png"))
  // 		  ->addComponent(new NetworkSendUpdateComponent()));
