#include	<iostream>

#include	"Window.hh"
#include	"World.hh"
#include	"Timer.hh"
#include	"StateManager.hh"
#include	"SFMLMenu.hh"

int			main()
{
  World		world;
  Timer		timer;
  StateManager states;

  states.pushState(new SFMLMenu(&world));
  try
    {
      while (42)
	{
	  timer.startFrame();
	  states.update();
	  if (timer.canTick())
	    {
	      std::cout << std::endl << "entities count = " << world.countEntities() << std::endl;
	      std::cout << "fps = " << timer.getCurrentFps() << std::endl;
	      states.render(timer);
	    }
	  timer.endFrame();
	}
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
  catch (std::string str)
    {
      std::cerr << str << std::endl;
    }
  catch (...)
    {
      std::cerr << "Unknown error." << std::endl;
    }
  return (0);
}
