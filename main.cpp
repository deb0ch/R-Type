#include	<iostream>

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"
#include	"SFMLInputSystem.hh"
#include	"PlayerMovementSystem.hh"

#include	"Pos2DComponent.hh"
#include	"Speed2DComponent.hh"
#include	"Friction2DComponent.hh"
#include	"Box2DComponent.hh"
#include	"SFMLSpriteComponent.hh"
#include	"MoveSystem.hh"
#include	"Entity.hh"
#include	"NetworkSystem.hh"
#include	"NetworkUpdateComponent.hh"
#include	"SFMLInputComponent.hh"
#include	"PlayerMovementComponent.hh"
#include	"MovementSpeedComponent.hh"

int		main()
{
  World		world;

  world.addSystem(new MoveSystem());
  world.addSystem(new Friction2DSystem());
  world.addSystem(new SFMLRenderSystem());
  world.addSystem(new PlayerMovementSystem());
  world.addSystem(new SFMLInputSystem());

  world.addEntity(world.createEntity()
  		  ->addComponent(new Pos2DComponent(100.0f, 100.0f))
  		  ->addComponent(new Box2DComponent(50.0f, 50.0f))
		  ->addComponent(new Speed2DComponent(5.f, 5.f))
		  ->addComponent(new Friction2DComponent(0.3))
		  ->addComponent(new SFMLSpriteComponent("sprites/ship.png"))
		  ->addComponent(new NetworkUpdateComponent())
		  ->addComponent(new SFMLInputComponent())
		  ->addComponent(new PlayerMovementComponent())
		  ->addComponent(new MovementSpeedComponent(5)));

  world.addEntity(world.createEntity()
  		  ->addComponent(new Pos2DComponent(200.0f, 200.0f))
  		  ->addComponent(new Box2DComponent(50.0f, 50.0f))
		  ->addComponent(new Speed2DComponent(5.f, 5.f))
		  ->addComponent(new Friction2DComponent(0.3))
		  ->addComponent(new SFMLSpriteComponent("sprites/ship.png"))
		  ->addComponent(new NetworkUpdateComponent())
		  ->addComponent(new SFMLInputComponent())
		  ->addComponent(new PlayerMovementComponent())
		  ->addComponent(new MovementSpeedComponent(2)));

  CollisionSystem *collision;

  collision = new CollisionSystem();
  world.addSystem(collision);
  world.addEventHandler("CollisionEvent", collision, &CollisionSystem::collision_event);

  NetworkSystem *network;
  std::vector<std::string> arg = {"Pos2DComponent"};

  network = new NetworkSystem(arg);
  world.addSystem(network);

  std::string test("Les pigouins ça glisse!");
  world.setSharedObject<std::string>("Test", &test);
  std::cout << *world.getSharedObject<std::string>("Test") << std::endl;
  std::cout << world.getSharedObject<ASystem>("NO-K") << std::endl;

  world.registerComponent(new Pos2DComponent());
  std::cout << world.createComponent("Pos2DComponent")->getType() << std::endl;

  world.start();
  for (;;)
    {
      world.process(0.16f);
      std::cout << std::endl;
    }
  world.stop();

  return (0);
}
