#include	"SFMLDisplaySystem.hh"

SFMLDisplaySystem::SFMLDisplaySystem()
  : ASystem("SFMLDisplaySystem")
{}

SFMLDisplaySystem::~SFMLDisplaySystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLDisplaySystem::canProcess(Entity *)
{
  return (false);
}

void		SFMLDisplaySystem::processEntity(Entity *, const float)
{}

void		SFMLDisplaySystem::start()
{
  if (!(this->_window = this->_world->getSharedObject<sf::RenderWindow>("sfmlwindow")))
    {
      this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "EpicGradius");
      this->_window->setVerticalSyncEnabled(true);
      this->_world->setSharedObject("sfmlwindow", this->_window);
    }
}

void		SFMLDisplaySystem::beforeProcess(const float)
{
  if (this->_window)
    this->_window->display();
}

void		SFMLDisplaySystem::afterProcess(const float)
{
  if (this->_window)
    this->_window->clear();
}
