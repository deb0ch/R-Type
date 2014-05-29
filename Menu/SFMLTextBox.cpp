#include <Windows.h>
#include <iostream>
#include "SFMLTextBox.hh"


SFMLTextBox::SFMLTextBox(sf::RenderWindow *window, float posX, float posY, 
	bool hasBorder, int charSize, int maxCharacters)
	: _window(window),
	_maxCharacters(maxCharacters),
	_charSize(charSize),
	_hasBorder(hasBorder)
{
	this->_text.setPosition(posX, posY);
	this->_text.setCharacterSize(charSize);
	this->_borders.setPosition(posX, posY);
	this->_borders.setOutlineThickness(10);
	this->_borders.setSize({ static_cast<float>(maxCharacters * charSize / 1.8f),
		static_cast<float>(charSize + 5) });
	this->_font = new sf::Font();
	if (this->_font->loadFromFile("Ressources/Fonts/gradius.ttf"))
	{
		this->_text.setFont(*_font);
	}
}

SFMLTextBox::~SFMLTextBox()
{
	delete this->_font;
}

void	SFMLTextBox::draw()
{
	if (this->_hasBorder)
		this->_window->draw(this->_borders);
	this->_window->draw(this->_text);
}

void	SFMLTextBox::addCharacter(char character)
{
	if (this->_string.size() >= this->_maxCharacters)
		return;
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
	if (string.size() >= this->_maxCharacters)
		return;
	this->_string = string;
	this->_text.setString(this->_string);
}

void SFMLTextBox::setColor(const sf::Color &color)
{
	this->_text.setColor(color);
}

void SFMLTextBox::setBorderSize(float width, float height)
{
	this->_borders.setSize({ width, height });
}

void SFMLTextBox::setBorderColor(const sf::Color &color)
{
	this->_borders.setFillColor(color);
}

void SFMLTextBox::setBorderOutLineColor(const sf::Color &color)
{
	this->_borders.setOutlineColor(color);
}