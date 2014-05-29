#include <Windows.h>
#include <iostream>
#include "SFMLButton.hh"


SFMLButton::SFMLButton(sf::RenderWindow *window, float posX, float posY, float width, float height)
: _window(window)
{
	this->_button = new sf::RectangleShape(sf::Vector2f(width, height));
	this->_button->setPosition(posX, posY);
}

SFMLButton::~SFMLButton()
{}

// a mettre dans une class button
bool	SFMLButton::isMouseOnButton()
{
	if (!this->_button)
		return (false);
	int y = sf::Mouse::getPosition(*this->_window).y;
	int x = sf::Mouse::getPosition(*this->_window).x;
	if (y > this->_button->getPosition().y
		&& y < this->_button->getPosition().y + this->_button->getSize().y
		&& x > this->_button->getPosition().x
		&& x < this->_button->getPosition().x + this->_button->getSize().x)
		return (true);
	return (false);
}

void	SFMLButton::draw()
{
	this->_window->draw(*this->_button);
}

void	SFMLButton::addTexture(const std::string &path, int width, int height)
{
	sf::Texture *texture = new sf::Texture();
	if (texture->loadFromFile(path))
	{
		this->_button->setTexture(texture);
		this->_button->setTextureRect(sf::IntRect(0, 0, width, height));
	}
}