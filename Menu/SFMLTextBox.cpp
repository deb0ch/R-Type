#include <Windows.h>
#include <iostream>
#include "SFMLTextBox.hh"


SFMLTextBox::SFMLTextBox(sf::RenderWindow *window, float posX, float posY,
	int charSize, int maxCharacters)
: _window(window), _maxCharacters(maxCharacters), _charSize(charSize)
{
	this->_text.setPosition(posX, posY);
	this->_borders.setPosition(posX, posY);
	this->_borders.setSize({ static_cast<float>(maxCharacters * charSize), static_cast<float>(charSize + 5) });
	this->_font = new sf::Font();
	if (!this->_font->loadFromFile("Ressources/Fonts/comic.ttf"))
	{
		this->_font = NULL;
	}
}

SFMLTextBox::~SFMLTextBox()
{
	delete this->_font;
}

void	SFMLTextBox::draw()
{
	this->_window->draw(this->_text);
	//this->_window->draw(this->_borders);
}

void	SFMLTextBox::addCharacter(char character)
{
	this->_string += character;
	this->_text.setString(this->_string);
}

void	SFMLTextBox::removelastCharacter()
{
	this->_string = this->_string.substr(0, this->_string.size() - 1);
	this->_text.setString(this->_string);
}

const std::string &SFMLTextBox::getString() const
{
	return (this->_string);
}

void SFMLTextBox::setString(const std::string &string)
{
	this->_string = string;
}

void SFMLTextBox::setColor(const sf::Color &color)
{
	this->_text.setColor(color);
}