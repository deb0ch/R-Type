#include	<iostream>

#include	"BarSystem.hh"
#include	"FooComponent.hh"
#include	"FooSystem.hh"
#include	"World.hh"

int		main()
{
  World		world;

  world.addSystem(new FooSystem())
    ->addSystem(new BarSystem());

  world.addEntity(world.createEntity())
    ->addComponent(new FooComponent(0));

  world.addEntity(world.createEntity())
    ->addComponent(new FooComponent(42));

  world.addEntity(world.createEntity());

  Entity *a;
  IComponent *b;

  a = world.createEntity();
  b = new FooComponent(5);
  a->addComponent(b);
  a->removeComponent(NULL);
  std::cout << a->hasComponent("FooComponent") << std::endl;
  delete a;

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
