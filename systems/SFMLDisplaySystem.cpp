#include	"SFMLDisplaySystem.hh"

SFMLDisplaySystem::SFMLDisplaySystem()
  : ASystem("SFMLDisplaySystem")
{}

SFMLDisplaySystem::~SFMLDisplaySystem()
{}

//----- ----- Methods ----- ----- //
bool		SFMLDisplaySystem::canProcess(Entity *entity)
{
  (void)entity;
  return (false);
}

void		SFMLDisplaySystem::processEntity(Entity *entity, const float)
{
  (void)entity;
}

void		SFMLDisplaySystem::start()
{
  this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "EpicGradius");
  this->_window->setVerticalSyncEnabled(true);
  this->_world->setSharedObject("sfmlwindow", this->_window);
}

void		SFMLDisplaySystem::beforeProcess(const float)
{
  this->_window->display();
}

void		SFMLDisplaySystem::afterProcess(const float)
{
  this->_window->clear();
}
