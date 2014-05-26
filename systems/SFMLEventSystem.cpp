#include	<iostream>
#include	<map>

#include	"SFMLEventSystem.hh"

#include	"SFMLKeyEvent.hh"

SFMLEventSystem::SFMLEventSystem()
  : ASystem("SFMLEventSystem")
{}

SFMLEventSystem::~SFMLEventSystem()
{}

void	SFMLEventSystem::init()
{
  this->_window = this->_world->getSharedObject<sf::RenderWindow>("sfmlwindow");
}

void	SFMLEventSystem::beforeProcess(const float)
{
  if (!this->_window)
    this->_window = this->_world->getSharedObject<sf::RenderWindow>("sfmlwindow");
  if (!this->_window)
    return ;

  sf::Event	event;
  while (this->_window->pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::KeyPressed:
	  this->_world->sendEvent(new SFMLKeyEvent(event.key.code, true));
	  break;

	case sf::Event::KeyReleased:
	  this->_world->sendEvent(new SFMLKeyEvent(event.key.code, false));
	  break;

	default:
	  break;
	}
    }
}

bool	SFMLEventSystem::canProcess(Entity *)
{
  return (false);
}

void	SFMLEventSystem::processEntity(Entity *, const float)
{}
