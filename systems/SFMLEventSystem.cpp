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
	  case sf::Event::Closed:
		  this->_window->close();
			  break;

	case sf::Event::KeyPressed:
	  this->_world->sendEvent(new SFMLKeyEvent(event.key.code, true));
	  break;

	case sf::Event::KeyReleased:
	  this->_world->sendEvent(new SFMLKeyEvent(event.key.code, false));
	  break;

	case sf::Event::MouseButtonPressed:
		std::cout << "MOUSE CLICK [" << sf::Mouse::getPosition().x << ";" << sf::Mouse::getPosition().y << "]" << std::endl;
		break;

	case sf::Event::MouseButtonReleased:
		std::cout << "MOUSE RELEASE [" << sf::Mouse::getPosition().x << ";" << sf::Mouse::getPosition().y << "]" << std::endl;
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
