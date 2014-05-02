#include	<iostream>

#include	"World.hh"
#include	"Entity.hh"

#include	"MoveSystem.hh"
#include	"CollisionSystem.hh"
#include	"SFMLRenderSystem.hh"

#include	"Pos2DComponent.hh"
#include	"Box2DComponent.hh"
#include	"SFMLSpriteComponent.hh"

int		main()
{
  World		world;

  world.addSystem(new MoveSystem());
  world.addSystem(new SFMLRenderSystem());

  world.addEntity(world.createEntity()
  		  ->addComponent(new Pos2DComponent(0.0f, 0.0f))
		  ->addComponent(new Box2DComponent(20.f, 20.f)));

  world.addEntity(world.createEntity()
		  ->addComponent(new Pos2DComponent(10.0f, 10.0f))
		  ->addComponent(new Box2DComponent(10.0f, 10.0f)));

  world.addEntity(world.createEntity()
  		  ->addComponent(new Pos2DComponent(100.0f, 100.0f))
  		  ->addComponent(new Box2DComponent(10.0f, 10.0f))
		  ->addComponent(new SFMLSpriteComponent("sprites/ship.png")));

  world.addSystem(new CollisionSystem());

  world.start();
  /**
   * Should be an infinite loop.
   * Delta time should be calculated and passed to World::process()
   */
  for (;;)
    {
      world.process(0.16f);
      std::cout << std::endl;
    }
  world.stop();

  return (0);
}
