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
	this->_buttonplay = new SFMLButton(this->_window, 25, 425, 400, 150);
	this->_ipServer = new SFMLTextBox(this->_window, 5, 350, false, 30);
	this->_ipServer->setString("ip server :");
	this->_ipServer->setColor(sf::Color(227, 55, 32));
	this->_textboxIP = new SFMLTextBox(this->_window, 170, 350, true, 30);
	this->_textboxIP->setColor(sf::Color::Color(255, 100, 100));
	this->_textboxIP->setBorderOutLineColor(sf::Color(227, 55, 32, 200));
	this->_textboxIP->setBorderColor(sf::Color::Color(255, 255, 255, 160));
	this->_buttonplay->addTexture("Ressources/Images/playgameButton.png", 250, 80);
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
	/*
	this->_font = new sf::Font();
	if (!this->_font->loadFromFile("Ressources/Fonts/comic.ttf"))
	{
		this->_font = NULL;
	}*/
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
			if (event.text.unicode == 13)
				return (0);
			else if (event.text.unicode == 8)
				this->_textboxIP->removelastCharacter();
			else
			{
				if ((event.text.unicode < '0' || event.text.unicode > '9') && event.text.unicode != '.')
					return (1);
				this->_textboxIP->addCharacter(static_cast<char>(event.text.unicode));
			}
			break;

		case sf::Event::MouseButtonPressed:
			return (!this->_buttonplay->isMouseOnButton());

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
	this->_window->draw(*this->_logo);
	this->_ipServer->draw();
	this->_buttonplay->draw();
	this->_textboxIP->draw();
	/*if (this->_font)
	{
		sf::Text Text;
		Text.setFont(*this->_font);
		Text.setString("ip address : " + this->_ipAddress);
		Text.setCharacterSize(50);
		Text.setPosition(0, 200);
		Text.setColor(sf::Color::Color(255, 100, 100));
		this->_window->draw(Text);
	}*/
	this->_window->display();
}

sf::RenderWindow *SFMLMenu::getWindow() const
{
	return (this->_window);
}

const std::string &SFMLMenu::getIpAddress() const
{
	return (this->_textboxIP->getString());
}