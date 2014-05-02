#include	<iostream>

#include	"World.hh"
#include	"Pos2DComponent.hh"
#include	"MoveSystem.hh"
#include	"Entity.hh"

int		main()
{
  World		world;

  world.addSystem(new MoveSystem());

  world.addEntity(world.createEntity()
  		  ->addComponent(new Pos2DComponent(0.0f, 0.0f)));

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
