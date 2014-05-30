#include "SFML/Window/WindowStyle.hpp"
#include "SFMLMenu.hh"
#include "Window.hh"
#include "StateManager.hh"
#include "StateRoom.hh"
#include "StateCredit.hh"
#include "ClientRelay.hh"
#include "Remote.hh"

SFMLMenu::SFMLMenu(World *world)
  : _world(world)
{
  this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32),
				       "EpicGradius", sf::Style::Titlebar | sf::Style::Close);
  this->_window->setVerticalSyncEnabled(true);
  this->init();
}

SFMLMenu::SFMLMenu(World *world, sf::RenderWindow *window)
  : _world(world)
{
  this->_window = window;
  this->_window->setVerticalSyncEnabled(true);
  this->init();
}

SFMLMenu::~SFMLMenu()
{}

void SFMLMenu::init()
{
  this->_background = NULL;
  this->_buttonplay = new SFMLButton(this->_window, 25, 425, 400, 150);
  this->_buttonplay->addTexture("Ressources/Images/playgameButton.png", 250, 80);
  this->_buttonCredit = new SFMLButton(this->_window, 540, 490, 250, 100);
  this->_buttonCredit->addTexture("Ressources/Images/creditsButton.png", 338, 94);
  this->_ipServer = new SFMLTextBox(this->_window, 5, 350, false, 30);
  this->_ipServer->setString("IP server :");
  this->_ipServer->setColor(sf::Color(229, 8, 54));
  this->_textboxIP = new SFMLTextBox(this->_window, 170, 350, true, 30);
  this->_textboxIP->setColor(sf::Color(255, 100, 100));
  this->_textboxIP->setBorderOutLineColor(sf::Color(227, 55, 32, 200));
  this->_textboxIP->setBorderColor(sf::Color(255, 255, 255, 160));
  sf::Texture *texture = new sf::Texture();
  if (texture->loadFromFile("Ressources/Images/menuBackground.jpg"))
    {
      this->_background = new sf::Sprite();
      this->_background->setTexture(*texture, true);
      this->_background->setScale(WINDOW_WIDTH / this->_background->getLocalBounds().width,
				  WINDOW_HEIGHT / this->_background->getLocalBounds().height);
    }
  sf::Texture *logo = new sf::Texture();
  if (logo->loadFromFile("Ressources/Images/logo.png"))
    {
      this->_logo = new sf::Sprite();
      this->_logo->setTexture(*logo, true);
      this->_logo->setPosition({ 100.0f, 0.0f });
      this->_logo->setScale(600 / this->_logo->getLocalBounds().width,
			    100 / this->_logo->getLocalBounds().height);
    }
  this->_world->setSharedObject<sf::RenderWindow>("sfmlwindow", this->_window);
}

void	SFMLMenu::connect()
{
	this->_relay = new ClientRelay(this->_textboxIP->getString(), 6667);
	if (!this->_relay->start())
		throw "butt";
	this->_world->setSharedObject("NetworkRelay", static_cast<INetworkRelay *>(this->_relay));
}

void SFMLMenu::update(StateManager& manager)
{
  sf::Event	event;
  while (this->_window->pollEvent(event))
    {
      switch (event.type)
	{
	case sf::Event::Closed:
	  this->_window->close();
	  break;

	case sf::Event::TextEntered:
	  if (event.text.unicode == 13)
	    {
	      this->connect();
		  manager.pushState(new StateRoom(this->_window, this->_world));
	    }
	  else if (event.text.unicode == 8)
	    this->_textboxIP->removelastCharacter();
	  else
	    {
	      if ((event.text.unicode < '0' || event.text.unicode > '9') && event.text.unicode != '.')
		return;
	      this->_textboxIP->addCharacter(static_cast<char>(event.text.unicode));
	    }
	  break;

	case sf::Event::MouseButtonPressed:
	  if (this->_buttonplay->isMouseOnButton())
	    {
	      this->connect();
		  manager.pushState(new StateRoom(this->_window, this->_world));
	    }
	  else if (this->_buttonCredit->isMouseOnButton())
	    manager.pushState(new StateCredit(this->_window));
	  return;

	default:
	  break;
	}
    }
}

void SFMLMenu::render(const Timer&)
{
  this->_window->clear();

  if (this->_background)
    this->_window->draw(*this->_background);
  this->_window->draw(*this->_logo);
  this->_ipServer->draw();
  this->_buttonplay->draw();
  this->_textboxIP->draw();
  this->_buttonCredit->draw();
  this->_window->display();
}

const std::string &SFMLMenu::getIpAddress() const
{
  return (this->_textboxIP->getString());
}
