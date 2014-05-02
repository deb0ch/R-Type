#include	<iostream>

#include	"World.hh"
#include	"Pos2DComponent.hh"
#include	"CollisionSystem.hh"
#include	"Box2DComponent.hh"
#include	"MoveSystem.hh"
#include	"Entity.hh"
#include	"Speed2DComponent.hh"

int		main()
{
  World		world;

  world.addSystem(new MoveSystem());

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
		  ->addComponent(new Speed2DComponent(5.f, 5.f)));

  CollisionSystem *collision;

  collision = new CollisionSystem();
  world.addSystem(collision);
  world.addEventHandler("CollisionEvent", collision, &CollisionSystem::collision_event);

  /*
   * Should be an infinite loop.
   * Delta time should be calculated and passed to World::process()
   */
  for (int i = 0 ; i < 3 ; i++)
    {
      world.process(0.16f);
      std::cout << std::endl;
    }

  return (0);
}
