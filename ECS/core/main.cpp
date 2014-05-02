#include	<iostream>

#include	"BarSystem.hh"
#include	"FooComponent.hh"
#include	"FooSystem.hh"
#include	"World.hh"

int		main()
{
  World		world;

  world.addSystem(new FooSystem());
  world.addSystem(new BarSystem());

  world.addEntity(world.createEntity()
		  ->addComponent(new FooComponent(0)));

  world.addEntity(world.createEntity()
		  ->addComponent(new FooComponent(42)));

  world.addEntity(world.createEntity());

  /**
   * Should be an infinite loop.
   * Delta time should be calculated and passed to World::process()
   */
  for (int i = 0 ; i < 3 ; i++)
    {
      world.process();
      std::cout << std::endl;
    }

  return (0);
}
