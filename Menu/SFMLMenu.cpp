#include <Windows.h>
#include <iostream>
#include "SFMLMenu.hh"
#include "Window.hh"


SFMLMenu::SFMLMenu()
{
	this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "EpicGradius");
	this->_window->setVerticalSyncEnabled(true);
	this->init();
}

SFMLMenu::SFMLMenu(sf::RenderWindow *window)
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
	this->_buttonplay = new SFMLButton(this->_window, 10, 270, 240, 100);
	this->_buttonplay->addTexture("Ressources/Images/playgameButton.png", 250, 80);
	sf::Texture *texture = new sf::Texture();
	if (texture->loadFromFile("Ressources/Images/menu.jpg"))
	{
		this->_background = new sf::Sprite();
		this->_background->setTexture(*texture, true);
		this->_background->setScale(WINDOW_WIDTH / this->_background->getLocalBounds().width,
			WINDOW_HEIGHT / this->_background->getLocalBounds().height);
	}
	this->_font = new sf::Font();
	if (!this->_font->loadFromFile("Ressources/Fonts/comic.ttf"))
	{
		this->_font = NULL;
	}
}

char SFMLMenu::update()
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
			std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
			std::cout << event.text.unicode << std::endl;
			if (event.text.unicode == 13)
				return (0);
			else if (event.text.unicode == 8)
				this->_ipAddress = this->_ipAddress.substr(0, this->_ipAddress.size() - 1);
			else
				this->_ipAddress += static_cast<char>(event.text.unicode);
			break;

		case sf::Event::MouseButtonPressed:
			std::cout << "MOUSE CLICK [" << sf::Mouse::getPosition(*this->_window).x << ";" << sf::Mouse::getPosition(*this->_window).y << "]" << std::endl;
			return (!this->_buttonplay->isMouseOnButton());
			break;

		default:
			break;
		}
	}
	return (1);
}

void SFMLMenu::render()
{
	Sleep(50);
	this->_window->clear();

	if (this->_background)
		this->_window->draw(*this->_background);
	this->_buttonplay->draw();

	if (this->_font)
	{
		sf::Text Text;
		Text.setFont(*this->_font);
		Text.setString("ip address : " + this->_ipAddress);
		Text.setCharacterSize(50);
		Text.setPosition(0, 200);
		Text.setColor(sf::Color::Color(255, 100, 100));
		this->_window->draw(Text);
	}
	this->_window->display();
}

sf::RenderWindow *SFMLMenu::getWindow() const
{
	return (this->_window);
}

const std::string &SFMLMenu::getIpAddress() const
{
	return (this->_ipAddress);
}