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

  try
    {
      states.pushState(new SFMLMenu(&world));
      while (states.isRunning())
	{
	  timer.startFrame();
	  states.update();
	  if (timer.canTick())
	    {
	      states.render(timer);
	    }
	  timer.endFrame();
	}
    }
  catch (const std::exception &e)
    {
      std::cerr << "Exception : " << e.what() << std::endl;
    }
  catch (const std::string &str)
    {
      std::cerr << "Error : " << str << std::endl;
    }
  catch (const char* &str)
    {
      std::cerr << "Error : " << str << std::endl;
    }
  catch (...)
    {
      std::cerr << "Error : Unknown error." << std::endl;
    }
  return (0);
}
