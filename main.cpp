#include	<iostream>

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"Friction2DSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"

#include	"Pos2DComponent.hh"
#include	"Speed2DComponent.hh"
#include	"Friction2DComponent.hh"
#include	"Box2DComponent.hh"
#include	"SFMLSpriteComponent.hh"
#include	"MoveSystem.hh"
#include	"Entity.hh"
#include	"NetworkSystem.hh"
#include	"NetworkUpdateComponent.hh"

int		main()
{
  World		world;

  world.addSystem(new MoveSystem());
  world.addSystem(new Friction2DSystem());
  world.addSystem(new SFMLRenderSystem());

  world.addEntity(world.createEntity()
  		  ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		  ->addComponent(new Box2DComponent(20.f, 20.f))
		  ->addComponent(new Speed2DComponent(1.f, 1.f)));

  world.addEntity(world.createEntity()
		  ->addComponent(new Pos2DComponent(10.0f, 10.0f))
		  ->addComponent(new Box2DComponent(10.0f, 10.0f))
		  ->addComponent(new Speed2DComponent(2.f, 2.f)));

  world.addEntity(world.createEntity()
  		  ->addComponent(new Pos2DComponent(100.0f, 100.0f))
  		  ->addComponent(new Box2DComponent(10.0f, 10.0f))
		  ->addComponent(new Speed2DComponent(5.f, 5.f))
		  ->addComponent(new Friction2DComponent())
		  ->addComponent(new SFMLSpriteComponent("sprites/ship.png"))
		  ->addComponent(new NetworkUpdateComponent()));

  CollisionSystem *collision;

  collision = new CollisionSystem();
  world.addSystem(collision);
  world.addEventHandler("CollisionEvent", collision, &CollisionSystem::collision_event);

  NetworkSystem *network;

  network = new NetworkSystem({"Pos2DComponent"});
  world.addSystem(network);

  world.start();
  for (;;)
    {
      world.process(0.16f);
      std::cout << std::endl;
    }
  world.stop();

  return (0);
}
