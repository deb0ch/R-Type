#include <Windows.h>
#include <iostream>
#include "SFMLMenu.hh"
#include "Window.hh"


SFMLMenu::SFMLMenu()
{
	this->_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "EpicGradius");
	this->_window->setVerticalSyncEnabled(true);
}

SFMLMenu::SFMLMenu(sf::RenderWindow *window)
{
	this->_window = window;
	this->_window->setVerticalSyncEnabled(true);
}

SFMLMenu::~SFMLMenu()
{}

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
			this->_ipAdress += static_cast<char>(event.text.unicode);
			break;

		case sf::Event::MouseButtonPressed:
			std::cout << "MOUSE CLICK [" << sf::Mouse::getPosition().x << ";" << sf::Mouse::getPosition().y << "]" << std::endl;
			return (0);
			break;

		case sf::Event::MouseButtonReleased:
			std::cout << "MOUSE RELEASE [" << sf::Mouse::getPosition().x << ";" << sf::Mouse::getPosition().y << "]" << std::endl;
			return (0);
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
	sf::Font font;
	// Load it from a file
	if (!font.loadFromFile("Ressources/Fonts/comic.ttf"))
	{
		return;
	}
	sf::Text Text;
	Text.setFont(font);
	Text.setString(this->_ipAdress);
	Text.setCharacterSize(24);
	Text.setColor(sf::Color::Red);
	this->_window->draw(Text);

	std::cout << "STRING" << this->_ipAdress << std::endl;
	this->_window->display();
}

sf::RenderWindow *SFMLMenu::getWindow() const
{
	return (this->_window);
}