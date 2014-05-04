#include <iostream>
#include "SFMLSpriteComponent.hh"
#include "ImageLoader.hh"

//----- ----- Constructors ----- ----- //
SFMLSpriteComponent::SFMLSpriteComponent(const std::string &filename)
  : AComponent("SFMLSpriteComponent"), _filaName(filename)
{}

SFMLSpriteComponent::SFMLSpriteComponent(const SFMLSpriteComponent &ref)
  : AComponent("SFMLSpriteComponent")
{
  this->_sprite = new sf::Sprite(*ref._sprite);
}

//----- ----- Destructor ----- ----- //
SFMLSpriteComponent::~SFMLSpriteComponent()
{
  delete this->_sprite;
}

//----- ----- Operators ----- ----- //
SFMLSpriteComponent	&SFMLSpriteComponent::operator=(const SFMLSpriteComponent &ref)
{
  this->_sprite = new sf::Sprite(*ref._sprite);
  return (*this);
}

//----- ----- Getters ----- ----- //
sf::Sprite	&SFMLSpriteComponent::getSprite() const
{
  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture();
  return (*this->_sprite);
}
