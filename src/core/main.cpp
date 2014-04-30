#include	<iostream>

#include	"FooSystem.hh"
#include	"World.hh"
#include	"FooComponent.hh"

void	create_entity_test(World &world)
{
  Entity *e;

  e = world.getEntity();
  e->addComponent(new FooComponent(15));
  world.addEntity(e);
}

int		main()
{
  World		world;

  world.addSystem(new FooSystem());

  create_entity_test(world);
  create_entity_test(world);
  create_entity_test(world);

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
