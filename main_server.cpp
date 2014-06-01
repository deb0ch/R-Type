#include	"ServerRelay.hh"

int		main()
{
  try
    {
      ServerRelay *server = new ServerRelay(6667, 42);
      server->start();
     }
  catch (const std::exception &e)
    {
      std::cerr << "Exception : " << e.what() << std::endl;
    }
  catch (const std::string &str)
    {
      std::cerr << "Error : " << str << std::endl;
    }
  catch (...)
    {
      std::cerr << "Error : Unknown error." << std::endl;
    }
  return (0);
}
