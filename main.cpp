#include	<iostream>

#include	"FooSystem.hh"
#include	"World.hh"
#include	"FooComponent.hh"

int		main()
{
  World		world;

  world.addSystem(new FooSystem());

  world.addEntity(world.getEntity()); //->addComponent(static_cast<IComponent *>(new FooComponent(12)))
  world.addEntity(world.getEntity()); //->addComponent(new FooComponent(12))
  world.addEntity(world.getEntity()); //->addComponent(new FooComponent(12))

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
