#include	<iostream>
#include	<map>

#include	"SFMLEventSystem.hh"

#include	"SFMLKeyEvent.hh"
#include	"SFMLJoystickEvent.hh"

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
	  this->_world->exit();
	  break;

	case sf::Event::KeyPressed:
	  this->_world->sendEvent(new SFMLKeyEvent(event.key.code, true));
	  break;

	case sf::Event::KeyReleased:
	  this->_world->sendEvent(new SFMLKeyEvent(event.key.code, false));
	  break;

	case sf::Event::JoystickMoved:
	  if (event.joystickMove.joystickId != 1)
	    break ;
	  if (event.joystickMove.axis == sf::Joystick::PovY
	      || event.joystickMove.axis == sf::Joystick::Y)
	    {
	      if (event.joystickMove.position > 50)
		this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::DOWN, true));
	      else if (event.joystickMove.position < -50)
		this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::UP, true));
	      else
		{
		  this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::UP, false));
		  this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::DOWN, false));
		}
	    }
	  if (event.joystickMove.axis == sf::Joystick::PovX
	      || event.joystickMove.axis == sf::Joystick::X)
	    {
	      if (event.joystickMove.position > 50)
		this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::RIGHT, true));
	      else if (event.joystickMove.position < -50)
		this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::LEFT, true));
	      else
		{
		  this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::RIGHT, false));
		  this->_world->sendEvent(new SFMLJoystickEvent(SFMLJoystickEvent::LEFT, false));
		}
	    }
	  break;

	case sf::Event::JoystickButtonPressed:
	  if (event.joystickButton.joystickId != 1)
	    break ;
	  this->_world->sendEvent(new SFMLJoystickEvent(event.joystickButton.button, true));
	  break;

	case sf::Event::JoystickButtonReleased:
	  if (event.joystickButton.joystickId != 1)
	    break ;
	  this->_world->sendEvent(new SFMLJoystickEvent(event.joystickButton.button, false));
	  break;

	case sf::Event::MouseButtonPressed:
	  //std::cout << "MOUSE CLICK [" << sf::Mouse::getPosition().x << ";" << sf::Mouse::getPosition().y << "]" << std::endl;
	  break;

	case sf::Event::MouseButtonReleased:
	  //std::cout << "MOUSE RELEASE [" << sf::Mouse::getPosition().x << ";" << sf::Mouse::getPosition().y << "]" << std::endl;
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
